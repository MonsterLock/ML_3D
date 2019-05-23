#include "ConsoleWindow.h"
#include "resource.h"
#include "windowsx.h"

LRESULT ConsoleWindow::HandleSubWndMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
		case WM_CREATE:
			{
				// Create edit control.
				HFONT hfDef;
				HWND hEdit;

				hEdit = CreateWindowEx(
					0,
					L"Edit",
					L"",
					WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
					0, 0, 0, 0,
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
				Edit_SetText(hEdit, L"HELLO");
				Edit_SetReadOnly( hEdit, TRUE );
				ToggleWindow( ID_VIEW_CONSOLEWINDOW, 2 );
			}
			break;
		case WM_COMMAND:
			{
				switch ( LOWORD( wParam ) )
				{
					case ID_VIEW_CONSOLEWINDOW:
						{
							ToggleWindow( ID_VIEW_CONSOLEWINDOW, 2 );
						}
						break;
				}
			}
			break;
		case WM_CLOSE:
			{
				ToggleWindow( ID_VIEW_CONSOLEWINDOW, 2 );
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

void ConsoleWindow::ToggleWindow( int item, int index )
{
	HMENU hFileMenu = GetSubMenu( GetMenu( GetParent( mParent ) ), index );
	DWORD isChecked = CheckMenuItem( hFileMenu, item, MF_BYCOMMAND );
	if ( isChecked == MF_UNCHECKED  )
	{
		CheckMenuItem( hFileMenu, item, MF_BYCOMMAND |  MF_CHECKED);
		ShowWindow(HSubWnd(), SW_SHOW);
	}
	else
	{
		CheckMenuItem( hFileMenu, item, MF_BYCOMMAND |  MF_UNCHECKED);
		ShowWindow(HSubWnd(), SW_HIDE);
	}
}
