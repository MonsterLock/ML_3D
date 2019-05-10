#include "MainWindow.h"
#include "resource.h"
#include <string>

#define _L(x)  __L(x)
#define __L(x)  L##x

void MainWindow::OnQuit()
{
	wchar_t szFileName[MAX_PATH];
	HINSTANCE hInstance = GetModuleHandle( nullptr );
	GetModuleFileName( hInstance, szFileName, MAX_PATH );

	std::wstring message =
		L"Project:\n" +
		static_cast< std::wstring >( szFileName ) +
		L"\n\nHas not saved the following file(s):\n" +
		_L( __FILE__ ) + // TODO: iterate through elements and check saved state
		L"\n\n\nEXIT WITHOUT SAVING?\n";

	switch ( MessageBox( m_hwnd, message.c_str(), L"EXIT", MB_YESNOCANCEL | MB_DEFBUTTON2 ) )
	{
		case IDYES:
			{
				DestroyWindow( m_hwnd );
				PostQuitMessage( 0 );
			}
			break;
		case IDNO:
			{
				// TODO save files
				DestroyWindow( m_hwnd );
				PostQuitMessage( 0 );
			}
			break;
		default:
			return;
	}
}

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
				OnQuit();
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
		case WM_COMMAND:
			switch ( LOWORD( wParam ) )
			{
				case ID_FILE_SAVE:
					{
						EnableMenuItem( m_hmenu, ID_FILE_SAVE, MF_GRAYED );
					}
					break;
				case ID_FILE_EXIT:
					{
						OnQuit();
					}
					break;
			}
		default:
			return DefWindowProc( m_hwnd, uMsg, wParam, lParam );
	}
	return TRUE;
}