#include "ConsoleWindow.h"
#include "resource.h"

LRESULT ConsoleWindow::HandleSubWndMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	HWND hFrame = GetParent(mParent);

	switch ( uMsg )
	{
		case WM_CREATE:
			{
				// Create edit control.
				HFONT hfDef;
				HWND hEdit;

				hEdit = CreateWindowEx(
					WS_EX_CLIENTEDGE,
					L"Edit",
					L"",
					WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
					0, 0, 100, 100,
					mSubWnd,
					reinterpret_cast< HMENU >( RID_MAIN_CLIENT ),
					GetModuleHandle( nullptr ),
					nullptr );

				if ( !hEdit )
				{
					MessageBox( mSubWnd, L"Could not create edit box.", L"ERROR", MB_OK | MB_ICONERROR );
				}

				hfDef = reinterpret_cast< HFONT >( GetStockObject( DEFAULT_GUI_FONT ) );
				SendMessage( hEdit, WM_SETFONT, static_cast< WPARAM >( RID_MAIN_CLIENT ), MAKELPARAM( FALSE, 0 ) );
			}
			break;
		case WM_MDIACTIVATE:
			{
				HMENU
					hMainMenu = GetMenu( hFrame ),
					hFileMenu = GetSubMenu( hMainMenu, 0 );
				UINT EnableFlag;

				if ( hFrame == reinterpret_cast< HWND >( lParam ) )
				{
					EnableFlag = MF_ENABLED;
				}
				else
				{
					EnableFlag = MF_GRAYED;
				}

				//EnableMenuItem( hMainMenu, 1, MF_BYPOSITION | EnableFlag );
				//EnableMenuItem( hMainMenu, 2, MF_BYPOSITION | EnableFlag );

				hFileMenu = GetSubMenu( hMainMenu, 0 );
				EnableMenuItem( hFileMenu, ID_FILE_SAVEAS, MF_BYCOMMAND | EnableFlag );
				//mainWnd->DoFileOpen( hwnd );
				DrawMenuBar( hFrame );
			}
			break;
		case WM_COMMAND:
			{
				switch ( LOWORD( wParam ) )
				{
					case ID_FILE_OPEN:
						{
							//mainWnd->DoFileOpen( hwnd );
						}
						break;
					case ID_FILE_SAVEAS:
						{
							//mainWnd->DoFileSave( hwnd );
						}
						break;
						//case ID_EDIT_CUT:
						//	SendDlgItemMessage( hwnd, RID_MAIN_CLIENT, WM_CUT, 0, 0 );
				}
			}
			break;
		case WM_SIZE:
			{
				HWND hEdit;
				RECT rcClient;

				// Calculate remaining height and size edit.
				GetClientRect( mSubWnd, &rcClient );
				hEdit = GetDlgItem( mSubWnd, RID_MAIN_CLIENT );
				SetWindowPos( hEdit, nullptr, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER );
			}
		default:
			{
				return DefMDIChildProc( mSubWnd, uMsg, wParam, lParam );
			}
	}

	return 0;
}
