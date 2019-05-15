#include "MainWindow.h"
#include "resource.h"
#include <Commctrl.h>
#include <string>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' "\
"version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define _L(x)  __L(x)
#define __L(x)  L##x
#define ID_MDI_FIRSTCHILD 50000

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

	switch ( MessageBox( mMDIFrame, message.c_str(), WindowText(), MB_YESNOCANCEL | MB_DEFBUTTON2 | MB_ICONWARNING ) )
	{
		case IDYES:
			{
				DestroyWindow( mMDIFrame );
				PostQuitMessage( 0 );
			}
			break;
		case IDNO:
			{
				// TODO save files
				DestroyWindow( mMDIFrame );
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
		mMDIFrame,
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
		case WM_CREATE:
			{
				// Register the MDI.
				WNDCLASSEX wc = { 0 };
				wc.cbSize = sizeof( wc );
				wc.style = CS_HREDRAW | CS_VREDRAW;
				wc.lpfnWndProc = MDIWndProc;
				wc.cbClsExtra = 0;
				wc.cbWndExtra = 0;
				wc.hInstance = GetModuleHandle( nullptr );
				wc.hbrBackground = CreateSolidBrush( RGB( 0, 0, 0 ) );// ( HBRUSH ) ( LTGRAY_BRUSH );
				wc.lpszMenuName = nullptr;
				wc.lpszClassName = L"MDICLIENT";
				wc.hIcon = static_cast< HICON >(
					LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 32, 32, 0 ) );
				wc.hIconSm = static_cast< HICON >(
					LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 16, 16, 0 ) );
				wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);

				if ( !RegisterClassEx( &wc ) )
				{
					MessageBox( nullptr, L"Registering MDI Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
					return FALSE;
				}

				// Create the MDI.
				CLIENTCREATESTRUCT ccs;

				// Retrieve the handle to the window menu and assign the first sub-window identifier.
				ccs.hWindowMenu = GetSubMenu( m_hmenu, 2 );
				ccs.idFirstChild = ID_MDI_FIRSTCHILD;

				RECT rc;
				GetClientRect( mMDIFrame, &rc );

				mMDIClient = CreateWindowEx(
					WS_EX_CLIENTEDGE,
					L"mdiclient",
					nullptr,
					WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE,
					rc.left, rc.top, rc.right, rc.bottom,
					mMDIFrame,
					m_hmenu,
					GetModuleHandle( nullptr ),
					&ccs );

				if ( !mMDIClient )
				{
					MessageBox( nullptr, L"Creating MDI Window Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
					return FALSE;
				}
			}
			break;
		case WM_CLOSE:
			{
				OnQuit();
				return 0;
			}
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint( mMDIFrame, &ps );
				FillRect( hdc, &ps.rcPaint, reinterpret_cast< HBRUSH > ( COLOR_WINDOW ) );
				EndPaint( mMDIFrame, &ps );
			}
			break;
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
			break;
		default:
			{
				return DefFrameProc( mMDIFrame, 0, uMsg, wParam, lParam );//mMDIClient, uMsg, wParam, lParam );
			}
	}
	return 0;
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

LRESULT CALLBACK MainWindow::MDIWndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if ( uMsg )
	{
		return DefMDIChildProc( hwnd, uMsg, wParam, lParam );
	}
	return 0;
}