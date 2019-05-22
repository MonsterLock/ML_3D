#include "MainWindow.h"
#include <Commctrl.h>
#include <string>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' "\
"version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define _L(x)  __L(x)
#define __L(x)  L##x
#define RES_STATUS

LRESULT MainWindow::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
		case WM_CREATE:
			{
				// Create window.
				consoleWindow.RegSubWnd(
					L"ConsoleWindow",
					CS_VREDRAW | CS_HREDRAW,
					LoadIcon( nullptr, IDI_WINLOGO ) );

				consoleWindow.CreateSubWnd(
					mMDIClient,
					MDIS_ALLCHILDSTYLES,
					CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT );

				// Create toolbar.
				tbMain.CreateToolbar( mMDIFrame, RID_MAIN_TB );

				// Create statusbar.
				sbMain.CreateStatusBar( mMDIFrame, RID_MAIN_STATUS );
			}
			break;
		case WM_SIZE:
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

				GetWindowRect( hTool, &rcTool );
				iToolHeight = rcTool.bottom - rcTool.top;

				// Size status bar window.
				hStatus = sbMain.GetStatusBar();
				SendMessage( hStatus, WM_SIZE, 0, 0 );

				GetWindowRect( hStatus, &rcStatus );
				iStatusHeight = rcStatus.bottom - rcStatus.top;

				// Calculate remaining height and size edit
				GetClientRect( mMDIFrame, &rcClient );
				iClientHeight = rcClient.bottom - iToolHeight - iStatusHeight;

				hClient = GetDlgItem( mMDIFrame, RID_MAIN_CLIENT );
				SetWindowPos( hClient, nullptr, 0, iToolHeight, rcClient.right, iClientHeight, SWP_NOZORDER );
			}
			break;
		case WM_COMMAND:
			if ( !GlobalCommands( uMsg, wParam, lParam ) )
			{
				if ( LOWORD( wParam ) >= ID_MDI_FIRSTCHILD )
				{
					return DefFrameProc( mMDIFrame, mMDIClient, WM_COMMAND, wParam, lParam );
				}
				else
				{
					HWND hChild = reinterpret_cast< HWND >( SendMessage( mMDIClient, WM_MDIGETACTIVE, 0, 0 ) );
					if ( hChild )
					{
						SendMessage( hChild, WM_COMMAND, wParam, lParam );
					}
				}
			}
			break;
		default:
			{
				return DefFrameProc( mMDIFrame, mMDIClient, uMsg, wParam, lParam );
			}
	}
	return 0;
}

BOOL MainWindow::GlobalCommands( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( LOWORD( wParam ) )
	{
		case ID_FILE_NEW:
			{

			}break;
		case ID_FILE_OPEN: {}break;
		case ID_FILE_STARTUP: {}break;
		case ID_FILE_SAVE: {}break;
		case ID_FILE_SAVEAS: {}break;
		case ID_FILE_SAVEALL: {}break;
		case ID_FILE_BUILDPROPERTIES: {} break;
		case ID_FILE_BUILDANDRUN: {} break;
		case ID_FILE_EXIT: {} break;
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
		case ID_VIEW_SCENEVIEW: {} break;
		case ID_VIEW_HIERARCHYWINDOW: {} break;
		case ID_VIEW_IN: {} break;
		case ID_VIEW_TOOLBAR: {} break;
		case ID_VIEW_GAMEVIEW: {} break;
		case ID_VIEW_CONSOLEWINDOW: {} break;
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
		default:
			{
				return FALSE;
			}
	}
	return TRUE;
}
//LRESULT CALLBACK MainWindow::SubWndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
//{
//	HWND hFrame = GetParent( GetParent( hwnd ) );
//	MainWindow* mainWnd = reinterpret_cast< MainWindow* >( GetWindowLongPtr( hFrame, GWLP_USERDATA ) );
//
//	switch ( uMsg )
//	{
//		case WM_CREATE:
//			{
//				if ( !mainWnd )
//				{
//					MessageBox( hwnd, L"Could not get parent window.", L"ERROR", MB_OK | MB_ICONERROR );
//				}
//				// Create edit control.
//				HFONT hfDef;
//				HWND hEdit;
//
//				hEdit = CreateWindowEx(
//					WS_EX_CLIENTEDGE,
//					L"Edit",
//					L"",
//					WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
//					0, 0, 100, 100,
//					hwnd,
//					reinterpret_cast< HMENU >( RID_MAIN_CLIENT ),
//					GetModuleHandle( nullptr ),
//					nullptr );
//
//				if ( !hEdit )
//				{
//					MessageBox( hwnd, L"Could not create edit box.", L"ERROR", MB_OK | MB_ICONERROR );
//				}
//
//				hfDef = reinterpret_cast< HFONT >( GetStockObject( DEFAULT_GUI_FONT ) );
//				SendMessage( hEdit, WM_SETFONT, static_cast< WPARAM >( RID_MAIN_CLIENT ), MAKELPARAM( FALSE, 0 ) );
//			}
//			break;
//		case WM_MDIACTIVATE:
//			{
//				HMENU
//					hMainMenu = GetMenu( hFrame ),
//					hFileMenu = GetSubMenu( hMainMenu, 0 );
//				UINT EnableFlag;
//
//				if ( hFrame == reinterpret_cast< HWND >( lParam ) )
//				{
//					EnableFlag = MF_ENABLED;
//				}
//				else
//				{
//					EnableFlag = MF_GRAYED;
//				}
//
//				//EnableMenuItem( hMainMenu, 1, MF_BYPOSITION | EnableFlag );
//				//EnableMenuItem( hMainMenu, 2, MF_BYPOSITION | EnableFlag );
//
//				hFileMenu = GetSubMenu( hMainMenu, 0 );
//				EnableMenuItem( hFileMenu, ID_FILE_SAVEAS, MF_BYCOMMAND | EnableFlag );
//				//EnableMenuItem( hFileMenu, ID_FILE_CLOSE, MF_BYCOMMAND | EnableFlag );
//				//EnableMenuItem( hFileMenu, ID_FILE_CLOSEALL, MF_BYCOMMAND | EnableFlag );
//				//mainWnd->DoFileOpen( hwnd );
//				DrawMenuBar( hFrame );
//			}
//			break;
//		case WM_COMMAND:
//			{
//				switch ( LOWORD( wParam ) )
//				{
//					case ID_FILE_OPEN:
//						{
//							//mainWnd->DoFileOpen( hwnd );
//						}
//						break;
//					case ID_FILE_SAVEAS:
//						{
//							//mainWnd->DoFileSave( hwnd );
//						}
//						break;
//						//case ID_EDIT_CUT:
//						//	SendDlgItemMessage( hwnd, RID_MAIN_CLIENT, WM_CUT, 0, 0 );
//				}
//			}
//			break;
//		case WM_SIZE:
//			{
//				HWND hEdit;
//				RECT rcClient;
//
//				// Calculate remaining height and size edit.
//				GetClientRect( hwnd, &rcClient );
//
//				hEdit = GetDlgItem( hwnd, RID_MAIN_CLIENT );
//				SetWindowPos( hEdit, nullptr, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER );
//			}
//		default:
//			{
//				return DefMDIChildProc( hwnd, uMsg, wParam, lParam );
//			}
//	}
//
//	return 0;
//}

//HWND MainWindow::CreateSubWindow( HWND hwnd )
//{
//	HWND hSub;
//
//	MDICREATESTRUCT mcs;
//	mcs.szTitle = L"[Untitled]";
//	mcs.szClass = L"TestSubWnd";
//	mcs.hOwner = GetModuleHandle( nullptr );
//	mcs.x = mcs.cx = CW_USEDEFAULT;
//	mcs.y = mcs.cy = CW_USEDEFAULT;
//	mcs.style = MDIS_ALLCHILDSTYLES;
//
//	hSub = reinterpret_cast< HWND >(
//		SendMessage( hwnd, WM_MDICREATE, 0, reinterpret_cast< LONG >( &mcs ) ) );
//
//	if ( !hSub )
//	{
//		MessageBox( hwnd, L"Sub-window creation failed.", L"ERROR",
//					MB_ICONEXCLAMATION | MB_OK );
//	}
//
//	return hSub;
//}
//
//BOOL MainWindow::RegSubWnd()
//{
//	WNDCLASSEX wc = { 0 };
//	wc.cbSize = sizeof( WNDCLASSEX );
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.lpfnWndProc = SubWndProc;
//	wc.lpszClassName = L"TestSubWnd";
//	wc.lpszMenuName = nullptr;
//	wc.hInstance = GetModuleHandle( nullptr );
//	wc.hbrBackground = reinterpret_cast< HBRUSH > ( COLOR_WINDOWFRAME );
//	wc.hIconSm = LoadIcon( nullptr, IDI_WINLOGO );
//
//	return RegisterClassEx( &wc ) ? TRUE : FALSE;
//}
