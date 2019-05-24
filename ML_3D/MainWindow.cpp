#include "MainWindow.h"
#include <Commctrl.h>
#include <string>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' "\
"version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define _L(x)  __L(x)
#define __L(x)  L##x
#define RES_STATUS

constexpr static float verticalDivide = 0.8f;
constexpr static float leftHorizontalDivide = 0.85f;
constexpr static float tabHeight = 0.03f;

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
				// Create scene window.
				sceneWindow.RegSubWnd(
					L"SceneWindow",
					0,
					LoadIcon( nullptr, IDI_WINLOGO ) );
				sceneWindow.CreateSubWnd(
					ClientWnd(),
					0 );

				// Create console window.
				consoleWindow.RegSubWnd(
					L"ConsoleWindow",
					0,
					LoadIcon( nullptr, IDI_WINLOGO ) );
				consoleWindow.CreateSubWnd(
					ClientWnd(),
					0 );

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
				if( !tabMain.CreateTabs( ClientWnd(), 0, L"TABMAIN" ) ||
					!tabProperties.CreateTabs( ClientWnd(), 0, L"TABPROPERTIES" ) ||
					!tabInfo.CreateTabs( ClientWnd(), TCS_BOTTOM, L"TABINFO" ) )
				{
					MessageBox( ClientWnd(), L"Could not create tab control(s).", L"ERROR", MB_OK | MB_ICONERROR );
				}

				TCITEM tab;
				tab.mask = TCIF_TEXT;

				tab.pszText = const_cast< LPWSTR >( L"Scene View" );
				TabCtrl_InsertItem( tabMain.GetTabControl(), 0, &tab );
				tab.pszText = const_cast< LPWSTR >( L"Game View" );
				TabCtrl_InsertItem( tabMain.GetTabControl(), 1, &tab );
				tab.pszText = const_cast< LPWSTR >( L"Animation View" );
				TabCtrl_InsertItem( tabMain.GetTabControl(), 2, &tab );

				tab.pszText = const_cast< LPWSTR >( L"Information" );
				TabCtrl_InsertItem( tabProperties.GetTabControl(), 3, &tab );
				tab.pszText = const_cast< LPWSTR >( L"Lighting" );
				TabCtrl_InsertItem( tabProperties.GetTabControl(), 4, &tab );

				tab.pszText = const_cast< LPWSTR >( L"Project" );
				TabCtrl_InsertItem( tabInfo.GetTabControl(), 5, &tab );
				tab.pszText = const_cast< LPWSTR >( L"Console" );
				TabCtrl_InsertItem( tabInfo.GetTabControl(), 6, &tab );
				tab.pszText = const_cast< LPWSTR >( L"Profiler" );
				TabCtrl_InsertItem( tabInfo.GetTabControl(), 7, &tab );
			}
			break;
		case WM_SIZE:
			{
				CallSize();
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
		case ID_VIEW_PROJECTWINDOW: {} break;
		case ID_VIEW_SCENEVIEW: { ToggleWindow( sceneWindow.Wnd(), ID_VIEW_SCENEVIEW, 2 ); } break;
		case ID_VIEW_HIERARCHYWINDOW: {} break;
		case ID_VIEW_IN: {} break;
		case ID_VIEW_TOOLBAR:
			{
				ToggleWindow( tbMain.GetToolbar(), ID_VIEW_TOOLBAR, 2 );
				CallSize();
			} break;
		case ID_VIEW_GAMEVIEW: {} break;
		case ID_VIEW_CONSOLEWINDOW: { ToggleWindow( consoleWindow.Wnd(), ID_VIEW_CONSOLEWINDOW, 2 ); } break;
		case ID_VIEW_ANI: {} break;
		case ID_VIEW_PROFILERWINDOW: {} break;
		case ID_VIEW_LIGHTINGWINDOW: {} break;
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

void MainWindow::ToggleWindow( HWND wnd, int item, int  index )
{
	HMENU hFileMenu = GetSubMenu( mMenu, index );
	if( IsWindowVisible( wnd ) )
	{
		CheckMenuItem( hFileMenu, item, MF_BYCOMMAND | MF_UNCHECKED );
		ShowWindow( wnd, SW_HIDE );
	}
	else
	{
		CheckMenuItem( hFileMenu, item, MF_BYCOMMAND | MF_CHECKED );
		ShowWindow( wnd, SW_SHOW );
	}
}

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
	SetWindowPos( hClient, nullptr,
				  0, iToolHeight, rcClient.right, iClientHeight,
				  SWP_NOZORDER );

	// Calculate sub-windows
	GetClientRect( hClient, &rcClient );

	int newVerticalDivide = static_cast< int >( rcClient.right * verticalDivide );

	SetWindowPos(
		tabMain.GetTabControl(),
		nullptr,
		0, 0,
		newVerticalDivide, static_cast< int >( rcClient.bottom * tabHeight ),
		SWP_SHOWWINDOW | SWP_NOZORDER );

	SetWindowPos(
		tabInfo.GetTabControl(),
		nullptr,
		0, static_cast< int >( rcClient.bottom * ( 1.0f - tabHeight ) ),
		newVerticalDivide, static_cast< int >( rcClient.bottom * tabHeight ),
		SWP_SHOWWINDOW | SWP_NOZORDER );

	SetWindowPos(
		sceneWindow.Wnd(),
		nullptr,
		0, static_cast< int >( rcClient.bottom * tabHeight ),
		newVerticalDivide, static_cast< int >( rcClient.bottom * ( leftHorizontalDivide - tabHeight ) ),
		SWP_NOZORDER );

	SetWindowPos(
		consoleWindow.Wnd(),
		nullptr,
		0, static_cast< int >( rcClient.bottom * leftHorizontalDivide ),
		newVerticalDivide, static_cast< int >( rcClient.bottom * ( 1.0f - leftHorizontalDivide - tabHeight ) ),
		SWP_NOZORDER );
}
