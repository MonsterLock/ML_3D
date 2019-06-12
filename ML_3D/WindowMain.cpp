#include "Global.h"
#include "WindowMain.h"

LRESULT WindowMain::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_CLOSE:
			{
				DestroyWindow( mHwnd );
				UnregisterClass(
					ClassName(),
					GetModuleHandle( nullptr )
				);
			}
			return 0;
		case WM_DESTROY:
			{
				PostQuitMessage( 0 );
			}
			break;
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint( mHwnd, &ps );
				EndPaint( mHwnd, &ps );
			}
			break;
		default:
			return DefWindowProc( mHwnd, uMsg, wParam, lParam );
	}
	return TRUE;
}
