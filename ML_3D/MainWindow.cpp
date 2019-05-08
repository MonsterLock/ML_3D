#include "MainWindow.h"

PCWSTR MainWindow::ClassName() const
{
	return L"ML_3D";
}

LRESULT MainWindow::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch ( uMsg )
	{
		case WM_CLOSE:
			{
				if ( MessageBox( m_hwnd, L"Really Quit?", L"ML_3D", MB_OKCANCEL ) == IDOK )
				{
					DestroyWindow( m_hwnd );
					PostQuitMessage( 0 );
				}
				// Else: User canceled. Do nothing.
			}
			return 0;
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint( m_hwnd, &ps );

				FillRect( hdc, &ps.rcPaint, reinterpret_cast< HBRUSH > ( COLOR_WINDOW ) );
			}
			return 0;

		default:
			return DefWindowProc( m_hwnd, uMsg, wParam, lParam );
	}
	return TRUE;
}