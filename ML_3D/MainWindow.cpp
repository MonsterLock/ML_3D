#include "MainWindow.h"
#include "resource.h"
#include <Commctrl.h>
#include <string>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' "\
"version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define _L(x)  __L(x)
#define __L(x)  L##x

void MainWindow::OnQuit()
{
	wchar_t szFileName[MAX_PATH];
	HINSTANCE hInstance = GetModuleHandle( nullptr );
	GetModuleFileName( hInstance, szFileName, MAX_PATH );

	std::wstring message =
		L"The project:\n\"" +
		static_cast< std::wstring >( szFileName ) +
		L"\"\nhas not saved [# of unsaved files] / [total number of project files].\n\nAre you sure you want to discard changes to:\n" +
		_L( __FILE__ ) + // TODO: iterate through elements and check saved state
		L"\n\nClick \"No\" to save all file(s)\n";

	switch ( MessageBox( m_hwnd, message.c_str(), WindowText(), MB_YESNOCANCEL | MB_DEFBUTTON2 | MB_ICONWARNING ) )
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

void MainWindow::OnAbout()
{
	DialogBox(
		GetModuleHandle( NULL ),
		MAKEINTRESOURCE( IDD_HELP_ABOUT_PAGE ),
		m_hwnd,
		AboutDlgProc );
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
				case ID_HELP_ABOUT:
					{
						OnAbout();
					}
					break;
			}
		default:
			{
				return DefFrameProc( m_hwnd, m_hMDIwnd, uMsg, wParam, lParam );
			}
	}
	return TRUE;
}

BOOL CALLBACK MainWindow::AboutDlgProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
		case WM_INITDIALOG:
			return true;
		case WM_COMMAND:
			switch ( LOWORD( wParam ) )
			{
				case IDOK:
					{
						EndDialog( hwnd, IDOK );
					}
					break;
				default: break;
			}

		case WM_NOTIFY:
			{
				// TODO
			}
		default:
			return FALSE;
	}
	return TRUE;
}
