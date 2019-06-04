#include "WindowConsole.h"
#include "windowsx.h"

/* Placeholder and was previously used for testing window panels */
LRESULT WindowConsole::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_CREATE:
			{
				// Create edit control.
				HWND hEdit = CreateWindowEx(
					0,
					L"Edit",
					L"",
					WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
					0, 0, 0, 0,
					Wnd(),
					reinterpret_cast< HMENU >( RID_MAIN_CLIENT ),
					GetModuleHandle( nullptr ),
					nullptr );

				if( !hEdit )
				{
					MessageBox( Wnd(), L"Could not create edit box.", L"ERROR", MB_OK | MB_ICONERROR );
				}
				Edit_SetText( hEdit, L"Console" );
				Edit_SetReadOnly( hEdit, TRUE );
			}
			break;
		case WM_SIZE:
			{
				// Calculate remaining height and size edit.
				HWND hEdit = GetDlgItem( Wnd(), RID_MAIN_CLIENT );
				RECT rcClient;
				GetClientRect( Wnd(), &rcClient );
				SetWindowPos( hEdit, nullptr, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER );
			}
		default:
			{
				return DefMDIChildProc( Wnd(), uMsg, wParam, lParam );
			}
	}
	return 0;
}
