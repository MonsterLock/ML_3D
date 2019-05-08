#include "MainWindow.h"

PCWSTR MainWindow::ClassName() const
{
	return m_lpClassName;
}

PCWSTR MainWindow::WindowText() const
{
	return m_lpWindowText;
}

LRESULT MainWindow::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
		case WM_CLOSE:
			{

				//if ( MessageBox( m_hwnd, L"Really Quit?", WindowText(), MB_OKCANCEL ) == IDOK )
				//{
				//	DestroyWindow( m_hwnd );
				//	PostQuitMessage( 0 );
				//}
				DestroyWindow( m_hwnd );
				PostQuitMessage( 0 );
				// Else: User canceled. Do nothing.
			}
			return 0;
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint( m_hwnd, &ps );
				FillRect( hdc, &ps.rcPaint, reinterpret_cast< HBRUSH > ( COLOR_WINDOW ) );
				EndPaint( m_hwnd, &ps );
			}
			return 0;

		default:
			return DefWindowProc( m_hwnd, uMsg, wParam, lParam );
	}
	return TRUE;
}