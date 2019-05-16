#include "MainWindow.h"
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
		GetModuleHandle( nullptr ),
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

void MainWindow::SetClientColor( HBRUSH color )
{
	mClientColor = color;
}

HBRUSH MainWindow::GetClientColor() const
{
	return mClientColor;
}

LRESULT MainWindow::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
		//case WM_NCCREATE:
		//	{
		//		MessageBox( nullptr, L"NCCREATE.", L"NCCREATE", MB_OK | MB_ICONEXCLAMATION );
		//	}
		case WM_CREATE:
			{
				mHmenu = GetMenu( mMDIFrame );

				// Create the MDI.
				m_lpMDIName = L"MDICLIENT";

				if ( !RegisterMDI( CreateSolidBrush( RGB( 255, 0, 255 ) ) ) ) // CreateSolidBrush( RGB( 255, 0, 255 ) );//reinterpret_cast< HBRUSH > ( COLOR_APPWORKSPACE );
				{
					MessageBox( nullptr, L"Registering MDI Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
					return FALSE;
				}

				// Retrieve the handle to the window menu and assign the first sub-window identifier.
				CLIENTCREATESTRUCT ccs;
				ccs.hWindowMenu = GetSubMenu( mHmenu, 5 );
				ccs.idFirstChild = ID_MDI_FIRSTCHILD;

				mMDIClient = CreateWindowEx(
					WS_EX_CLIENTEDGE,
					GetMDIName(),
					nullptr,
					WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
					CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
					mMDIFrame,
					0,
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
		//case WM_PAINT:
		//	{
		//		PAINTSTRUCT ps;
		//		HDC hdc = BeginPaint( mMDIClient, &ps );
		//		FillRect( hdc, &ps.rcPaint, GetClientColor() );
		//		EndPaint( mMDIClient, &ps );
		//		//DrawMenuBar( mMDIFrame );
		//	}
		//	break;
		//case WM_SIZE:
		//	{
		//		RECT rcFrame;
		//		GetClientRect( mMDIFrame, &rcFrame );
		//		SetWindowPos( mMDIClient, nullptr, rcFrame.left, rcFrame.top, rcFrame.right, rcFrame.bottom, SWP_DRAWFRAME );
		//
		//		//int iMDIHeight;
		//
		//		//iMDIHeight = rcClient.bottom -
		//
		//		//RECT rcFrame;
		//		//GetClientRect( mMDIClient, &rcFrame );
		//	}
		//	break;
			//case WM_COMMAND:
			//	switch ( LOWORD( wParam ) )
			//	{
			//		case ID_FILE_SAVE:
			//			{
			//				EnableMenuItem( mHmenu, ID_FILE_SAVE, //MF_GRAYED );
			//			}
			//			break;
			//		case ID_FILE_EXIT:
			//			{
			//				OnQuit();
			//			}
			//			break;
			//		case ID_HELP_ABOUT:
			//			{
			//				OnAbout();
			//			}
			//			break;
			//		default:
			//			{
			//				if ( LOWORD( wParam ) >= ID_MDI_FIRSTCHILD )
			//				{
			//					return DefFrameProc( mMDIFrame, //mMDIClient, uMsg, wParam, lParam );
			//				}
			//				else
			//				{
			//					HWND hChild = reinterpret_cast< HWND >//( SendMessage( mMDIClient, WM_MDIGETACTIVE, 0, /0 ) );
			//					if ( hChild )
			//					{
			//						SendMessage( hChild, WM_COMMAND, //wParam, lParam );
			//					}
			//				}
			//			}
			//	}
			//	break;
		default:
			{
				return DefFrameProc( mMDIFrame, mMDIClient, uMsg, wParam, lParam );//mMDIClient, uMsg, wParam, lParam );
			}
	}
	return 0;
}

BOOL MainWindow::RegisterMDI( const HBRUSH color )
{
	SetClientColor( color );

	WNDCLASSEX wc = { 0 };

	wc.cbSize = sizeof( WNDCLASSEX );
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = reinterpret_cast<WNDPROC>(MDIWndProc);
	wc.lpszClassName = L"CLIENT WINDOW";
	wc.lpszMenuName = nullptr;// reinterpret_cast< LPCWSTR >( NULL );
	wc.hInstance = GetModuleHandle( nullptr );
	wc.hCursor = LoadCursor( nullptr, IDC_ARROW );
	wc.hbrBackground = GetClientColor();
	wc.hIcon = static_cast< HICON >(
		LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 32, 32, 0 ) );
	wc.hIconSm = static_cast< HICON >(
		LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 16, 16, 0 ) );

	return RegisterClassEx( &wc ) ? TRUE : FALSE;
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