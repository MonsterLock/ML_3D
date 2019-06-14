#include "Global.h"
#include "WindowProfiler.h"

/* Placeholder and was previously used for testing window panels */
LRESULT WindowProfiler::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_CREATE:
			{
				// Create edit control.
				HWND hEdit;

				hEdit = CreateWindowEx(
					0,
					L"Edit",
					L"",
					WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
					0, 0, 0, 0,
					Wnd(),
					reinterpret_cast< HMENU >( RID_MAIN_CLIENT ),
					GetModuleHandle( nullptr ),
					nullptr );

				TESTRESULT( !hEdit );
				Edit_SetText( hEdit, L"Profiler" );
				Edit_SetReadOnly( hEdit, TRUE );
			}
			break;
		case WM_COMMAND:
			{
				break;
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