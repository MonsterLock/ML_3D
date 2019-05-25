#include "MainWindow.h"
#include <Commctrl.h>
#include <string>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' "\
"version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define _L(x)  __L(x)
#define __L(x)  L##x
#define RES_STATUS

constexpr static float
tabRatio = 0.03f,
verticalRatio = 0.8f,
leftHorizontalRatio = 0.85f,
rightHorizontalRatio = 0.33f;

LRESULT MainWindow::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_GETDLGCODE:
			{
				if( wParam == VK_ESCAPE )
				{
					SendMessage( FrameWnd(), WM_CLOSE, 0, 0 );
				}
			}
			break;
		case WM_CLOSE:
			{
				MessageBox( nullptr, L"Think you're gonig to exit?", L"NOPE", MB_OK | MB_ICONEXCLAMATION );
				/* TODO:
				- Save window configurations
				- Check for any unsaved work
				- Clean resources */
			}
			break;
		case WM_CREATE:
			{
				// Create windows.
				animationWindow.RegSubWnd( L"AnimationWindow", 0, LoadIcon( nullptr, IDI_WINLOGO ) );
				animationWindow.CreateSubWnd( ClientWnd(), 0 );

				consoleWindow.RegSubWnd( L"ConsoleWindow", 0, LoadIcon( nullptr, IDI_WINLOGO ) );
				consoleWindow.CreateSubWnd( ClientWnd(), 0 );

				gameWindow.RegSubWnd( L"GameWindow", 0, LoadIcon( nullptr, IDI_WINLOGO ) );
				gameWindow.CreateSubWnd( ClientWnd(), 0 );

				hierarchyWindow.RegSubWnd( L"HierarchyWindow", 0, LoadIcon( nullptr, IDI_WINLOGO ) );
				hierarchyWindow.CreateSubWnd( ClientWnd(), 0 );

				informationWindow.RegSubWnd( L"InformationWindow", 0, LoadIcon( nullptr, IDI_WINLOGO ) );
				informationWindow.CreateSubWnd( ClientWnd(), 0 );

				lightingWindow.RegSubWnd( L"LightingWindow", 0, LoadIcon( nullptr, IDI_WINLOGO ) );
				lightingWindow.CreateSubWnd( ClientWnd(), 0 );

				profilerWindow.RegSubWnd( L"ProfilerWindow", 0, LoadIcon( nullptr, IDI_WINLOGO ) );
				profilerWindow.CreateSubWnd( ClientWnd(), 0 );

				projectWindow.RegSubWnd( L"ProjectWindow", 0, LoadIcon( nullptr, IDI_WINLOGO ) );
				projectWindow.CreateSubWnd( ClientWnd(), 0 );

				sceneWindow.RegSubWnd( L"SceneWindow", 0, LoadIcon( nullptr, IDI_WINLOGO ) );
				sceneWindow.CreateSubWnd( ClientWnd(), 0 );

				// Create toolbar.
				if( !tbMain.CreateToolbar( FrameWnd(), RID_MAIN_TB ) )
				{
					MessageBox( ClientWnd(), L"Could not create toolbar.", L"ERROR", MB_OK | MB_ICONERROR );
				}

				// Create statusbar.
				if( !sbMain.CreateStatusBar( FrameWnd(), RID_MAIN_STATUS ) )
				{
					MessageBox( ClientWnd(), L"Could not create statusbar.", L"ERROR", MB_OK | MB_ICONERROR );
				}

				// Create tabs controls
				if( !tabView.CreateTabs( ClientWnd(), 0, L"TABMAIN" ) ||
					!tabProperties.CreateTabs( ClientWnd(), 0, L"TABPROPERTIES" ) ||
					!tabInfo.CreateTabs( ClientWnd(), TCS_BOTTOM, L"TABINFO" ) )
				{
					MessageBox( ClientWnd(), L"Could not create tab control(s).", L"ERROR", MB_OK | MB_ICONERROR );
				}

				TCITEM tab;
				tab.mask = TCIF_TEXT;

				tab.pszText = const_cast< LPWSTR >( L"Scene View" );
				TabCtrl_InsertItem( tabView.GetTabControl(), 0, &tab );
				tab.pszText = const_cast< LPWSTR >( L"Game View" );
				TabCtrl_InsertItem( tabView.GetTabControl(), 1, &tab );
				tab.pszText = const_cast< LPWSTR >( L"Animation View" );
				TabCtrl_InsertItem( tabView.GetTabControl(), 2, &tab );
				currentViewWnd = sceneWindow.Wnd();

				tab.pszText = const_cast< LPWSTR >( L"Project" );
				TabCtrl_InsertItem( tabInfo.GetTabControl(), 0, &tab );
				tab.pszText = const_cast< LPWSTR >( L"Console" );
				TabCtrl_InsertItem( tabInfo.GetTabControl(), 1, &tab );
				tab.pszText = const_cast< LPWSTR >( L"Profiler" );
				TabCtrl_InsertItem( tabInfo.GetTabControl(), 2, &tab );
				currentInfoWnd = projectWindow.Wnd();

				currentCategoryWnd = hierarchyWindow.Wnd();

				tab.pszText = const_cast< LPWSTR >( L"Information" );
				TabCtrl_InsertItem( tabProperties.GetTabControl(), 0, &tab );
				tab.pszText = const_cast< LPWSTR >( L"Lighting" );
				TabCtrl_InsertItem( tabProperties.GetTabControl(), 1, &tab );
				currentPropertiesWnd = informationWindow.Wnd();

				ShowWindow( currentViewWnd, SW_SHOW );
				ShowWindow( currentInfoWnd, SW_SHOW );
				ShowWindow( currentCategoryWnd, SW_SHOW );
				ShowWindow( currentPropertiesWnd, SW_SHOW );
			}
			break;
		case WM_SIZE:
			{
				CallSize();
			}
			break;
		case WM_NOTIFY:
			{
				if( HIWORD( wParam ) == TCN_SELCHANGE )
				{
					int
						tabViewIndex = SendMessage( tabView.GetTabControl(), TCM_GETCURSEL, 0, 0 ),
						tabInfoIndex = SendMessage( tabInfo.GetTabControl(), TCM_GETCURSEL, 0, 0 ),
						tabCategoryIndex = 0,
						tabPropertiesIndex = SendMessage( tabProperties.GetTabControl(), TCM_GETCURSEL, 0, 0 );

					HWND
						tabViewSelect = ViewPanel( tabViewIndex ),
						tabInfoSelect = InfoPanel( tabInfoIndex ),
						tabCategorySelect = CategoryPanel( tabCategoryIndex ),
						tabPropertiesSelect = PropertiesPanel( tabPropertiesIndex );

					ChangeTabs( currentViewWnd, tabViewSelect );
					ChangeTabs( currentInfoWnd, tabInfoSelect );
					ChangeTabs( currentCategoryWnd, tabCategorySelect );
					ChangeTabs( currentPropertiesWnd, tabPropertiesSelect );
					CallSize();
				}
			}
			break;
		case WM_COMMAND:
			if( !GlobalCommands( uMsg, wParam, lParam ) )
			{
				if( LOWORD( wParam ) >= ID_MDI_FIRSTCHILD )
				{
					return DefFrameProc( FrameWnd(), ClientWnd(), WM_COMMAND, wParam, lParam );
				}
				else
				{
					HWND hChild = reinterpret_cast< HWND >( SendMessage( ClientWnd(), WM_MDIGETACTIVE, 0, 0 ) );
					if( hChild )
					{
						SendMessage( hChild, WM_COMMAND, wParam, lParam );
					}
				}
			}
			break;
		default:
			{
				return DefFrameProc( FrameWnd(), ClientWnd(), uMsg, wParam, lParam );
			}
	}
	return 0;
}

BOOL MainWindow::GlobalCommands( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( LOWORD( wParam ) )
	{
		case ID_FILE_NEW: {}break;
		case ID_FILE_OPEN: {}break;
		case ID_FILE_STARTUP: {}break;
		case ID_FILE_SAVE: {}break;
		case ID_FILE_SAVEAS: {}break;
		case ID_FILE_SAVEALL: {}break;
		case ID_FILE_BUILDPROPERTIES: {} break;
		case ID_FILE_BUILDANDRUN: {} break;
		case ID_FILE_EXIT: { SendMessage( FrameWnd(), WM_CLOSE, 0, 0 ); } break;
		case ID_GOTO_FILE: {} break;
		case ID_GOTO_OBJECT: {} break;
		case ID_GOTO_LASTEDIT: {} break;
		case ID_EDIT_FIND: {} break;
		case ID_EDIT_FINDREPLACE: {} break;
		case ID_NEXT_FILE: {} break;
		case ID_NEXT_OBJECT: {} break;
		case ID_PREVIOUS_FILE: {} break;
		case ID_PREVIOUS_OBJECT: {} break;
		case ID_EDIT_UNDO: {} break;
		case ID_EDIT_REDO: {} break;
		case ID_Menu: {} break;
		case ID_EDIT_COPY: {} break;
		case ID_EDIT_PASTE: {} break;
		case ID_EDIT_DELETE: {} break;
		case ID_EDIT_SELECTALL: {} break;
		case ID_EDIT_SELECTIONGROUP: {} break;
		case ID_VIEW_TOOLBAR:
			{
				if( IsWindowVisible( tbMain.GetToolbar() ) )
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_VIEWPANEL, MF_BYCOMMAND | MF_UNCHECKED );
					ShowWindow( tbMain.GetToolbar(), SW_HIDE );

				}
				else
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_VIEWPANEL, MF_BYCOMMAND | MF_CHECKED );
					ShowWindow( tbMain.GetToolbar(), SW_SHOW );
				}
				CallSize();
			} break;
		case ID_VIEW_VIEWPANEL:
			{
				if( IsWindowVisible( tabView.GetTabControl() ) )
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_VIEWPANEL, MF_BYCOMMAND | MF_UNCHECKED );
					ShowWindow( tabView.GetTabControl(), SW_HIDE );
					ShowWindow( currentViewWnd, SW_HIDE );
				}
				else
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_VIEWPANEL, MF_BYCOMMAND | MF_CHECKED );
					ShowWindow( tabView.GetTabControl(), SW_SHOW );
					ShowWindow( currentViewWnd, SW_SHOW );
				}
				CallSize();
			} break;
		case ID_VIEW_CATEGORYPANEL:
			{
				if( IsWindowVisible( hierarchyWindow.Wnd() ) )
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_CATEGORYPANEL, MF_BYCOMMAND | MF_UNCHECKED );
					ShowWindow( currentCategoryWnd, SW_HIDE );
				}
				else
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_CATEGORYPANEL, MF_BYCOMMAND | MF_CHECKED );
					ShowWindow( currentCategoryWnd, SW_SHOW );
				}
				CallSize();
			} break;
		case ID_VIEW_PROPERTIESPANEL:
			{
				if( IsWindowVisible( tabProperties.GetTabControl() ) )
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_PROPERTIESPANEL, MF_BYCOMMAND | MF_UNCHECKED );
					ShowWindow( tabProperties.GetTabControl(), SW_HIDE );
					ShowWindow( currentPropertiesWnd, SW_HIDE );
				}
				else
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_PROPERTIESPANEL, MF_BYCOMMAND | MF_CHECKED );
					ShowWindow( tabProperties.GetTabControl(), SW_SHOW );
					ShowWindow( currentPropertiesWnd, SW_SHOW );
				}
				CallSize();
			} break;
		case ID_VIEW_SYSTEMPANEL:
			{
				if( IsWindowVisible( tabInfo.GetTabControl() ) )
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_SYSTEMPANEL, MF_BYCOMMAND | MF_UNCHECKED );
					ShowWindow( tabInfo.GetTabControl(), SW_HIDE );
					ShowWindow( currentInfoWnd, SW_HIDE );
				}
				else
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_SYSTEMPANEL, MF_BYCOMMAND | MF_CHECKED );
					ShowWindow( tabInfo.GetTabControl(), SW_SHOW );
					ShowWindow( currentInfoWnd, SW_SHOW );
				}
				CallSize();
			} break;
		case ID_VIEW_WIREFRAME: {} break;
		case ID_VIEW_ORTHOGRAPHIC: {} break;
		case ID_VIEW_PERSPECTIVE: {} break;
		case ID_PROJECT_ADDNEW: {} break;
		case ID_PROJECT_ADDEXISTING: {} break;
		case ID_SHOWALL_WINDOWS: {} break;
		case ID_SHOWALL_VIEWS: {} break;
		case ID_SHOWALL_FILES: {} break;
		case ID_SHOWALL_OBJECTS: {} break;
		case ID_PROJECT_PROPERTIES: {} break;
		case ID_TOOLS_CREATEELEMENT: {} break;
		case ID_TOOLS_CREATESUB: {} break;
		case ID_3DELEMENT_CUBE: {} break;
		case ID_3DELEMENT_SPHERE: {} break;
		case ID_3DELEMENT_CAPSULE: {} break;
		case ID_3DELEMENT_CYLINDER: {} break;
		case ID_3DELEMENT_PLANE: {} break;
		case ID_3DELEMENT_QUAD: {} break;
		case ID_3DELEMENT_TERRAIN: {} break;
		case ID_2DELEMENT_SPRITE: {} break;
		case ID_2DELEMENT_SPRITEMASK: {} break;
		case ID_2DELEMENT_TILEMAP: {} break;
		case ID_EFFECTS_PARTICLESYSTEM: {} break;
		case ID_EFFECTS_TRAIL: {} break;
		case ID_EFFECTS_LINE: {} break;
		case ID_LIGHT_DIRECTIONAL: {} break;
		case ID_LIGHT_POINT: {} break;
		case ID_LIGHT_SPOT: {} break;
		case ID_LIGHT_AREA: {} break;
		case ID_LIGHT_REFLECTIONPROBE: {} break;
		case ID_TOOLS_AUDIO: {} break;
		case ID_TOOLS_VIDEO: {} break;
		case ID_TOOLS_UI: {} break;
		case ID_TOOLS_CAMERA: {} break;
		case ID_TOOLS_SCRIPT: {} break;
		case ID_TOOLS_SHADER: {} break;
		case ID_TOOLS_SCENE: {} break;
		case ID_TOOLS_MAKE: {} break;
		case ID_TOOLS_CLEARSET: {} break;
		case ID_TOOLS_SETASFIRSTELEMENT: {} break;
		case ID_TOOLS_SETASSECONDELEMENT: {} break;
		case ID_TOOLS_MOVETOELEMENT: {} break;
		case ID_TOOLS_MOVETOORIGIN: {} break;
		case ID_TOOLS_SETGAMEVIEW: {} break;
		case ID_TOOLS_TOGGLEACTIVE: {} break;
		case ID_WINDOW_FLOAT: {} break;
		case ID_WINDOW_FLOATALL: {} break;
		case ID_WINDOW_DOCK: {} break;
		case ID_WINDOW_AUTOHIDE: {} break;
		case ID_WINDOW_HIDE: {} break;
		case ID_WINDOW_LAYOUTS: {} break;
		case ID_WINDOW_SAVEWINDOWLAYOUT: {} break;
		case ID_WINDOW_APPLYWINDOWLAYOUT: {} break;
		case ID_WINDOW_MANAGEWINDOWLAYOUT: {} break;
		case ID_WINDOW_RESETWINDOWLAYOUT: {} break;
		case ID_HELP_ABOUT: {} break;
		case ID_HELP_VIEWHELP: {} break;
		case ID_HELP_REPORTABUG: {} break;
		default: return FALSE;
	}
	return TRUE;
}

HWND MainWindow::ViewPanel( int index )
{
	switch( index )
	{
		case 0: { return sceneWindow.Wnd(); } break;
		case 1: { return gameWindow.Wnd(); }break;
		case 2: { return animationWindow.Wnd(); }break;
		default:return nullptr;
	}
}

HWND MainWindow::InfoPanel( int index )
{
	switch( index )
	{
		case 0: { return projectWindow.Wnd(); } break;
		case 1: { return consoleWindow.Wnd(); }break;
		case 2: { return profilerWindow.Wnd(); }break;
		default:return nullptr;
	}
}

HWND MainWindow::CategoryPanel( int index )
{
	switch( index )
	{
		case 0: { return hierarchyWindow.Wnd(); } break;
		default:return nullptr;
	}
}

HWND MainWindow::PropertiesPanel( int index )
{
	switch( index )
	{
		case 0: { return informationWindow.Wnd(); } break;
		case 1: { return lightingWindow.Wnd(); }break;
		default:return nullptr;
	}
}

void MainWindow::ChangeTabs( HWND currentTab, HWND newTab )
{
	if( currentTab != newTab )
	{
		ShowWindow( currentTab, SW_HIDE );
		ShowWindow( newTab, SW_SHOW );
		currentTab = newTab;
	}
}

// TODO: Clean this
void MainWindow::CallSize()
{
	HWND
		hClient,
		hTool,
		hStatus;

	RECT
		rcClient,
		rcTool,
		rcStatus;

	int
		iClientHeight,
		iToolHeight,
		iStatusHeight;

	// Size toolbar window.
	hTool = tbMain.GetToolbar();
	SendMessage( hTool, TB_AUTOSIZE, 0, 0 );

	if( IsWindowVisible( hTool ) )
	{
		GetWindowRect( hTool, &rcTool );
		iToolHeight = rcTool.bottom - rcTool.top;
	}
	else
	{
		iToolHeight = 0;
	}

	// Size status bar window.
	hStatus = sbMain.GetStatusBar();
	SendMessage( hStatus, WM_SIZE, 0, 0 );

	GetWindowRect( hStatus, &rcStatus );
	iStatusHeight = rcStatus.bottom - rcStatus.top;

	// Calculate remaining height and size edit
	GetClientRect( FrameWnd(), &rcClient );
	iClientHeight = rcClient.bottom - iToolHeight - iStatusHeight;

	hClient = GetDlgItem( FrameWnd(), RID_MAIN_CLIENT );
	SetWindowPos( hClient, nullptr, 0, iToolHeight, rcClient.right, iClientHeight, SWP_NOZORDER );

	// Calculate sub-windows
	GetClientRect( hClient, &rcClient );

	int
		tabHeight = static_cast< int >( rcClient.bottom * tabRatio ),
		verticalDivide = verticalDivide = static_cast< int >( rcClient.right * verticalRatio ),
		rightWidth = rcClient.right - verticalDivide,
		leftHorizontalDivide = static_cast< int >( rcClient.bottom * leftHorizontalRatio ),
		rightHorizontalDivide = static_cast< int >( rcClient.bottom * rightHorizontalRatio );

	char clientState = 0x00;

	if( IsWindowVisible( tabView.GetTabControl() ) ) { clientState ^= 1 << 0; }
	if( IsWindowVisible( tabInfo.GetTabControl() ) ) { clientState ^= 1 << 1; }
	if( IsWindowVisible( hierarchyWindow.Wnd() ) ) { clientState ^= 1 << 2; }
	if( IsWindowVisible( tabProperties.GetTabControl() ) ) { clientState ^= 1 << 3; }

	switch( static_cast< unsigned int >( clientState ) )
	{
		case 0: { return; }
		case 1:
			{
				verticalDivide = rcClient.right;
				leftHorizontalDivide = rcClient.bottom;
			} break;
		case 2:
			{
				verticalDivide = rcClient.right;
				leftHorizontalDivide = 0;
			} break;
		case 3:
			{
				verticalDivide = rcClient.right;
				leftHorizontalDivide = static_cast< int >( rcClient.bottom * leftHorizontalRatio );
			} break;
		case 4:
			{
				verticalDivide = 0;
				rightWidth = rcClient.right;
				rightHorizontalDivide = rcClient.bottom;
			} break;
		case 5:
			{
				verticalDivide = static_cast< int >( rcClient.right * verticalRatio );
				rightWidth = rcClient.right - verticalDivide;
				leftHorizontalDivide = rcClient.bottom;
				rightHorizontalDivide = rcClient.bottom;
			} break;
		case 6:
			{
				verticalDivide = static_cast< int >( rcClient.right * verticalRatio );
				rightWidth = rcClient.right - verticalDivide;
				leftHorizontalDivide = 0;
				rightHorizontalDivide = rcClient.bottom;
			} break;
		case 7:
			{
				verticalDivide = static_cast< int >( rcClient.right * verticalRatio );
				rightWidth = rcClient.right - verticalDivide;
				leftHorizontalDivide = static_cast< int >( rcClient.bottom * leftHorizontalRatio );
				rightHorizontalDivide = rcClient.bottom;
			} break;
		case 8:
			{
				verticalDivide = 0;
				rightWidth = rcClient.right;
				rightHorizontalDivide = 0;
			} break;
		case 9:
			{
				verticalDivide = static_cast< int >( rcClient.right * verticalRatio );
				rightWidth = rcClient.right - verticalDivide;
				leftHorizontalDivide = rcClient.bottom;
				rightHorizontalDivide = 0;

			} break;
		case 10:
			{
				verticalDivide = static_cast< int >( rcClient.right * verticalRatio );
				rightWidth = rcClient.right - verticalDivide;
				leftHorizontalDivide = 0;
				rightHorizontalDivide = 0;
			} break;
		case 11:
			{
				verticalDivide = static_cast< int >( rcClient.right * verticalRatio );
				rightWidth = rcClient.right - verticalDivide;
				leftHorizontalDivide = static_cast< int >( rcClient.bottom * leftHorizontalRatio );
				rightHorizontalDivide = 0;
			} break;
		case 12:
			{
				verticalDivide = 0;
				rightWidth = rcClient.right;
				rightHorizontalDivide = static_cast< int >( rcClient.bottom * rightHorizontalRatio );
			} break;
		case 13:
			{
				verticalDivide = static_cast< int >( rcClient.right * verticalRatio );
				rightWidth = rcClient.right - verticalDivide;
				leftHorizontalDivide = rcClient.bottom;
				rightHorizontalDivide = static_cast< int >( rcClient.bottom * rightHorizontalRatio );
			} break;
		case 14:
			{
				verticalDivide = static_cast< int >( rcClient.right * verticalRatio );
				rightWidth = rcClient.right - verticalDivide;
				leftHorizontalDivide = 0;
				rightHorizontalDivide = static_cast< int >( rcClient.bottom * rightHorizontalRatio );
			} break;
		case 15:
			{
				verticalDivide = verticalDivide = static_cast< int >( rcClient.right * verticalRatio );
				rightWidth = rcClient.right - verticalDivide;
				leftHorizontalDivide = static_cast< int >( rcClient.bottom * leftHorizontalRatio );
				rightHorizontalDivide = static_cast< int >( rcClient.bottom * rightHorizontalRatio );
			} break;

		default:
			break;
	}

	// Top-Left Panel
	SetWindowPos( tabView.GetTabControl(), nullptr, 0, 0, verticalDivide, tabHeight, SWP_NOZORDER );
	SetWindowPos( currentViewWnd, nullptr, 0, tabHeight, verticalDivide, leftHorizontalDivide - tabHeight, SWP_NOZORDER );

	// Bot-Left Panel
	SetWindowPos( tabInfo.GetTabControl(), nullptr, 0, rcClient.bottom - tabHeight, verticalDivide, tabHeight, SWP_NOZORDER );
	SetWindowPos( currentInfoWnd, nullptr, 0, leftHorizontalDivide, verticalDivide, rcClient.bottom - leftHorizontalDivide - tabHeight, SWP_NOZORDER );

	// Top-Right Panel
	SetWindowPos( currentCategoryWnd, nullptr, verticalDivide, 0, rightWidth, rightHorizontalDivide, SWP_NOZORDER );

	// Bot-Right Panel
	SetWindowPos( tabProperties.GetTabControl(), nullptr, verticalDivide, rightHorizontalDivide, rightWidth, tabHeight, SWP_NOZORDER );
	SetWindowPos( currentPropertiesWnd, nullptr, verticalDivide, rightHorizontalDivide + tabHeight, rightWidth, rcClient.bottom - rightHorizontalDivide - tabHeight, SWP_NOZORDER );
}
