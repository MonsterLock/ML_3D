#include "MainWindow.h"
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

LRESULT MainWindow::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
		case WM_CLOSE:
			{
				OnQuit();
				return 0;
			}
		case WM_CREATE:
			{
				if ( !RegisterMDIChild( CreateSolidBrush( RGB( 255, 0, 255 ) ) ) )
				{
					MessageBox( nullptr, L"Registering MDI Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
					return FALSE;
				}
			}
			break;
		case WM_COMMAND:
			switch ( LOWORD( wParam ) )
			{
				case ID_FILE_SAVE:
					{
						EnableMenuItem( mMenu, ID_FILE_SAVE, MF_GRAYED );
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
				default:
					{
						break;
						//if ( LOWORD( wParam ) >= ID_MDI_FIRSTCHILD )
						//{
						//	return DefFrameProc( mMDIFrame, mMDIClient, uMsg, wParam, lParam );
						//}
						//else
						//{
						//	HWND hChild = reinterpret_cast< HWND >( SendMessage( mMDIClient, WM_MDIGETACTIVE, 0, 0 ) );
						//	if ( hChild )
						//	{
						//		SendMessage( hChild, WM_COMMAND, wParam, lParam );
						//	}
						//}
					}
			}
			break;
		default:
			{
				return DefFrameProc( mMDIFrame, mMDIClient, uMsg, wParam, lParam );
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

LRESULT CALLBACK MainWindow::SubWndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if ( uMsg )
	{
		return DefMDIChildProc( hwnd, uMsg, wParam, lParam );
	}

	return 0;
}

HWND MainWindow::CreateSubWindow( HWND hMDIClient )
{
	HWND hSub;

	MDICREATESTRUCT mcs;
	mcs.szTitle;
	mcs.szClass;
	mcs.hOwner = GetModuleHandle( nullptr );
	mcs.x = mcs.cx = CW_USEDEFAULT;
	mcs.y = mcs.cy = CW_USEDEFAULT;
	mcs.style = MDIS_ALLCHILDSTYLES;

	hSub = reinterpret_cast< HWND >(
		SendMessage( mMDIClient, WM_MDICREATE, 0, reinterpret_cast< LONG >( &mcs ) ) );

	if ( !hSub )
	{
		MessageBox( mMDIClient, L"Sub-window creation failed.", L"ERROR",
					MB_ICONEXCLAMATION | MB_OK );
	}
	return hSub;
}

BOOL MainWindow::RegSubWnd()
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof( WNDCLASSEX );
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = SubWndProc;
	wc.lpszClassName = L"TestSubWnd";
	wc.lpszMenuName = nullptr;
	wc.hInstance = GetModuleHandle( nullptr );
	wc.hbrBackground = CreateSolidBrush( RGB( 255, 69, 0 ) );

	return RegisterClassEx( &wc ) ? TRUE : FALSE;
}
