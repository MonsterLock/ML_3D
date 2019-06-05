#include "MainWindow.h"
#include <Commctrl.h>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' "\
"version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

constexpr static float
tabRatio = 0.03f,
verticalRatio = 0.8f,
leftHorizontalRatio = 0.85f,
rightHorizontalRatio = 0.33f;

LRESULT MainWindow::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_CLOSE:
			{
				/* TODO:
				- Save window configurations
				- Check for any unsaved work
				- Clean resources */
				if( MainMenu() )
					DestroyMenu( MainMenu() );
				DestroyWindow( FrameWnd() );
				UnregisterClass(
					FrameName(),
					GetModuleHandle( nullptr )
				);
			}
			return 0;
		case WM_DESTROY:
			{
				PostQuitMessage( 0 );
			}
			break;
		case WM_CREATE:
			{
				// Create windows.
				animationWnd.RegSubWnd( 0, nullptr );
				animationWnd.CreateSubWnd( ClientWnd(), 0 );

				consoleWnd.RegSubWnd( 0, nullptr );
				consoleWnd.CreateSubWnd( ClientWnd(), 0 );

				gameWnd.RegSubWnd( 0, nullptr );
				gameWnd.CreateSubWnd( ClientWnd(), 0 );

				hierarchyWnd.RegSubWnd( 0, nullptr );
				hierarchyWnd.CreateSubWnd( ClientWnd(), 0 );

				lightingWnd.RegSubWnd( 0, nullptr );
				lightingWnd.CreateSubWnd( ClientWnd(), 0 );

				profilerWnd.RegSubWnd( 0, nullptr );
				profilerWnd.CreateSubWnd( ClientWnd(), 0 );

				projectWnd.RegSubWnd( 0, nullptr );
				projectWnd.CreateSubWnd( ClientWnd(), 0 );

				propertiesWnd.RegSubWnd( 0, nullptr );
				propertiesWnd.CreateSubWnd( ClientWnd(), 0 );

				sceneWnd.RegSubWnd( CS_OWNDC, nullptr );
				sceneWnd.CreateSubWnd( ClientWnd(), 0 );

				// Create toolbar.
				tbMain.Create( FrameWnd(), nullptr, 0, reinterpret_cast< HMENU >( RID_MAIN_TB ) );

				TBADDBITMAP tbab; // Toolbar images
				tbab.hInst = HINST_COMMCTRL;
				tbab.nID = IDB_STD_SMALL_COLOR;
				SendMessage( tbMain.Wnd(), TB_ADDBITMAP, 0, reinterpret_cast< LPARAM >( &tbab ) );

				TBBUTTON tbb[3]; // Toolbar buttons
				ZeroMemory( tbb, sizeof( tbb ) );
				Toolbar::SetToolButton( tbb, 0, ID_FILE_NEW, STD_FILENEW, BTNS_BUTTON, TBSTATE_ENABLED );
				Toolbar::SetToolButton( tbb, 1, ID_FILE_OPEN, STD_FILEOPEN, BTNS_BUTTON, TBSTATE_ENABLED );
				Toolbar::SetToolButton( tbb, 2, ID_FILE_SAVEAS, STD_FILESAVE, BTNS_BUTTON, TBSTATE_ENABLED );
				SendMessage( tbMain.Wnd(), TB_ADDBUTTONS, sizeof( tbb ) / sizeof( TBBUTTON ), reinterpret_cast< LPARAM >( &tbb ) );

				// Create statusbar.
				sbMain.Create( FrameWnd(), nullptr, 0, reinterpret_cast< HMENU >( RID_MAIN_STATUS ) );
				sbMain.SetText( 0, L"Welcome." );

				// Create tabs controls.
				TCITEM tab;
				tab.mask = TCIF_TEXT;

				tabView.Create( FrameWnd(), L"TABMAIN", 0, nullptr );
				tabView.AddTab( 0, tab, L"Scene" );
				tabView.AddTab( 1, tab, L"Game" );
				tabView.AddTab( 2, tab, L"Animation" );

				tabInfo.Create( FrameWnd(), L"TABINFO", TCS_BOTTOM, nullptr );
				tabInfo.AddTab( 0, tab, L"Project" );
				tabInfo.AddTab( 1, tab, L"Console" );
				tabInfo.AddTab( 2, tab, L"Profiler" );

				tabProperties.Create( FrameWnd(), L"TABPROPERTIES", TCS_BOTTOM, nullptr );
				tabProperties.AddTab( 0, tab, L"Properties" );
				tabProperties.AddTab( 1, tab, L"Lighting" );

				// Create font.
				HDC hdc;
				long lfHeight;
				hdc = GetDC( nullptr );
				lfHeight = -MulDiv( 12, GetDeviceCaps( hdc, LOGPIXELSY ), 72 );
				ReleaseDC( nullptr, hdc );

				hf = CreateFont( lfHeight, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, const_cast< LPCWSTR >( L"Consolas" ) );

				EnumChildWindows( FrameWnd(), reinterpret_cast< WNDENUMPROC >( SetFont ), reinterpret_cast< LPARAM >( hf ) );

				// Set and show current windows.
				currentViewWnd = sceneWnd.Wnd();
				ShowWindow( currentViewWnd, SW_SHOW );

				currentInfoWnd = projectWnd.Wnd();
				ShowWindow( currentInfoWnd, SW_SHOW );

				currentCategoryWnd = hierarchyWnd.Wnd();
				ShowWindow( currentCategoryWnd, SW_SHOW );

				currentPropertiesWnd = propertiesWnd.Wnd();
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
				int
					tabViewIndex = TabCtrl_GetCurSel( tabView.Wnd() ),
					tabInfoIndex = TabCtrl_GetCurSel( tabInfo.Wnd() ),
					tabCategoryIndex = 0,
					tabPropertiesIndex = TabCtrl_GetCurSel( tabProperties.Wnd() );

				HWND
					tabViewSelect = ViewPanel( tabViewIndex ),
					tabInfoSelect = InfoPanel( tabInfoIndex ),
					tabCategorySelect = CategoryPanel( tabCategoryIndex ),
					tabPropertiesSelect = PropertiesPanel( tabPropertiesIndex );

				ChangeTabs( currentViewWnd, tabViewSelect );
				ChangeTabs( currentInfoWnd, tabInfoSelect );
				ChangeTabs( currentCategoryWnd, tabCategorySelect );
				ChangeTabs( currentPropertiesWnd, tabPropertiesSelect );
			}
			break;
		case WM_COMMAND:
			{
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
			}
			break;
		default:
				return DefFrameProc( FrameWnd(), ClientWnd(), uMsg, wParam, lParam );
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
				if( IsWindowVisible( tbMain.Wnd() ) )
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_TOOLBAR, MF_BYCOMMAND | MF_UNCHECKED );
					ShowWindow( tbMain.Wnd(), SW_HIDE );
				}
				else
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_TOOLBAR, MF_BYCOMMAND | MF_CHECKED );
					ShowWindow( tbMain.Wnd(), SW_SHOW );
				}
				CallSize();
			} break;
		case ID_VIEW_VIEWPANEL:
			{
				if( IsWindowVisible( tabView.Wnd() ) )
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_VIEWPANEL, MF_BYCOMMAND | MF_UNCHECKED );
					ShowWindow( tabView.Wnd(), SW_HIDE );
					ShowWindow( currentViewWnd, SW_HIDE );
				}
				else
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_VIEWPANEL, MF_BYCOMMAND | MF_CHECKED );
					ShowWindow( tabView.Wnd(), SW_SHOW );
					ShowWindow( currentViewWnd, SW_SHOW );
				}
				CallSize();
			} break;
		case ID_VIEW_CATEGORYPANEL:
			{
				if( IsWindowVisible( hierarchyWnd.Wnd() ) )
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
				if( IsWindowVisible( tabProperties.Wnd() ) )
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_PROPERTIESPANEL, MF_BYCOMMAND | MF_UNCHECKED );
					ShowWindow( tabProperties.Wnd(), SW_HIDE );
					ShowWindow( currentPropertiesWnd, SW_HIDE );
				}
				else
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_PROPERTIESPANEL, MF_BYCOMMAND | MF_CHECKED );
					ShowWindow( tabProperties.Wnd(), SW_SHOW );
					ShowWindow( currentPropertiesWnd, SW_SHOW );
				}
				CallSize();
			} break;
		case ID_VIEW_SYSTEMPANEL:
			{
				if( IsWindowVisible( tabInfo.Wnd() ) )
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_SYSTEMPANEL, MF_BYCOMMAND | MF_UNCHECKED );
					ShowWindow( tabInfo.Wnd(), SW_HIDE );
					ShowWindow( currentInfoWnd, SW_HIDE );
				}
				else
				{
					CheckMenuItem( GetSubMenu( mMenu, 2 ), ID_VIEW_SYSTEMPANEL, MF_BYCOMMAND | MF_CHECKED );
					ShowWindow( tabInfo.Wnd(), SW_SHOW );
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
		case ID_HELP_ABOUT:
			{
				DialogBox( GetModuleHandle( nullptr ), MAKEINTRESOURCE( IDD_HELP_ABOUT_PAGE ), FrameWnd(), AboutDlg );
			} break;
		case ID_HELP_VIEWHELP: {} break;
		case ID_HELP_REPORTABUG: {} break;

		default: return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK MainWindow::SetFont( HWND hwnd, LPARAM font )
{
	SendMessage( hwnd, WM_SETFONT, font, true );
	return true;
}

HWND MainWindow::ViewPanel( int index )
{
	switch( index )
	{
		case 0: { return sceneWnd.Wnd(); } break;
		case 1: { return gameWnd.Wnd(); }break;
		case 2: { return animationWnd.Wnd(); }break;
		default: return nullptr;
	}
}

HWND MainWindow::InfoPanel( int index )
{
	switch( index )
	{
		case 0: { return projectWnd.Wnd(); } break;
		case 1: { return consoleWnd.Wnd(); }break;
		case 2: { return profilerWnd.Wnd(); }break;
		default: return nullptr;
	}
}

HWND MainWindow::CategoryPanel( int index )
{
	switch( index )
	{
		case 0: { return hierarchyWnd.Wnd(); } break;
		default: return nullptr;
	}
}

HWND MainWindow::PropertiesPanel( int index )
{
	switch( index )
	{
		case 0: { return propertiesWnd.Wnd(); } break;
		case 1: { return lightingWnd.Wnd(); }break;
		default: return nullptr;
	}
}

void MainWindow::ChangeTabs( HWND& currentTab, HWND& newTab )
{
	if( currentTab != newTab )
	{
		ShowWindow( currentTab, SW_HIDE );
		currentTab = newTab;
		CallSize();
		ShowWindow( currentTab, SW_SHOW );
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
	hTool = tbMain.Wnd();
	SendMessage( hTool, TB_AUTOSIZE, 0, 0 );

	if( IsWindowVisible( hTool ) )
	{
		GetWindowRect( hTool, &rcTool );
		iToolHeight = rcTool.bottom - rcTool.top;
	}
	else iToolHeight = 0;

	// Size status bar window.
	hStatus = sbMain.Wnd();
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

	unsigned int clientState = 0x0;

	if( IsWindowVisible( tabView.Wnd() ) ) { clientState = 0xF; }
	if( IsWindowVisible( tabInfo.Wnd() ) ) { clientState = ( clientState | 0xF0 ); }
	if( IsWindowVisible( hierarchyWnd.Wnd() ) ) { clientState = ( clientState | 0xF00 ); }
	if( IsWindowVisible( tabProperties.Wnd() ) ) { clientState = ( clientState | 0xF000 ); }

	if( !clientState ) return;

	switch( clientState & 0xFF )
	{
		case 0x0F: { leftHorizontalDivide = rcClient.bottom; } break;
		case 0xF0: { leftHorizontalDivide = 0; }break;
		case 0xFF: { leftHorizontalDivide = static_cast< int >( rcClient.bottom * leftHorizontalRatio ); }break;
		default: { clientState = ( clientState | 0xF0000 ); } break;
	}
	switch( ( clientState & 0xFF00 ) >> 8 )
	{
		case 0x0F: { rightHorizontalDivide = rcClient.bottom; }break;
		case 0xF0: { rightHorizontalDivide = 0; }break;
		case 0xFF: { rightHorizontalDivide = static_cast< int >( rcClient.bottom * rightHorizontalRatio ); }break;
		default: { clientState = ( clientState | 0xF00000 ); } break;
	}
	switch( ( clientState & 0xFF0000 ) >> 16 )
	{
		case 0x00: { verticalDivide = static_cast< int >( rcClient.right * verticalRatio ); }break;
		case 0x0F: { verticalDivide = 0; }break;
		case 0xF0: { verticalDivide = rcClient.right; }break;
	}
	rightWidth = rcClient.right - verticalDivide;

	// Top-Left Panel
	SetWindowPos( tabView.Wnd(), HWND_TOP, 0, iToolHeight, verticalDivide, tabHeight, SWP_NOOWNERZORDER );
	SetWindowPos( currentViewWnd, nullptr, 0, tabHeight, verticalDivide, leftHorizontalDivide - tabHeight, SWP_NOZORDER );

	// Bot-Left Panel
	SetWindowPos( tabInfo.Wnd(), HWND_TOP, 0, rcClient.bottom - tabHeight + iToolHeight, verticalDivide, tabHeight, SWP_NOOWNERZORDER );
	SetWindowPos( currentInfoWnd, nullptr, 0, leftHorizontalDivide, verticalDivide, rcClient.bottom - leftHorizontalDivide - tabHeight, SWP_NOZORDER );

	// Top-Right Panel
	SetWindowPos( currentCategoryWnd, nullptr, verticalDivide, 0, rightWidth, rightHorizontalDivide, SWP_NOZORDER );

	// Bot-Right Panel
	SetWindowPos( tabProperties.Wnd(), HWND_TOP, verticalDivide, rcClient.bottom - tabHeight + iToolHeight, rightWidth, tabHeight, SWP_NOOWNERZORDER );
	SetWindowPos( currentPropertiesWnd, nullptr, verticalDivide, rightHorizontalDivide, rightWidth, rcClient.bottom - rightHorizontalDivide - tabHeight, SWP_NOZORDER );
}

BOOL CALLBACK MainWindow::AboutDlg( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			switch( LOWORD( wParam ) )
			{
				case IDOK:
					EndDialog( hwnd, IDOK );
					break;
			}
			break;
		default:
			return FALSE;
	}
	return TRUE;
}