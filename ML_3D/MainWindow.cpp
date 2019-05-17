#include "MainWindow.h"
#include <Commctrl.h>
#include <string>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' "\
"version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define _L(x)  __L(x)
#define __L(x)  L##x
#define RES_STATUS

#define RID_MAIN_TB 1338
#define RID_MAIN_STATUS 1339

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

BOOL MainWindow::LoadTextFileToEdit( HWND hEdit, LPCWSTR pszFileName )
{
	HANDLE hFile;
	BOOL bSuccess = FALSE;

	hFile = CreateFile(
		pszFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		nullptr,
		OPEN_EXISTING,
		0,
		nullptr );

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD dwFileSize;

		dwFileSize = GetFileSize( hFile, nullptr );

		if ( dwFileSize != 0xFFFFFFFF )
		{
			LPWSTR pszFileText;

			pszFileText = reinterpret_cast< LPWSTR > ( GlobalAlloc( GPTR, dwFileSize + 1 ) );

			if ( pszFileText )
			{
				DWORD dwRead;

				if ( ReadFile( hFile, pszFileText, dwFileSize, &dwRead, nullptr ) )
				{
					pszFileText[dwFileSize] = 0;
					if ( SetWindowText( hEdit, pszFileText ) )
					{
						bSuccess = TRUE;
					}
				}
				GlobalFree( pszFileText );
			}
		}
		CloseHandle( hFile );
	}
	return bSuccess;
}

BOOL MainWindow::SaveTextFileFromEdit( HWND hEdit, LPCWSTR pszFileName )
{
	HANDLE hFile;
	BOOL bSuccess = FALSE;

	hFile = CreateFile(
		pszFileName,
		GENERIC_WRITE,
		0,
		nullptr,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		nullptr );

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD dwFileSize;

		dwFileSize = GetFileSize( hFile, nullptr );

		if ( dwFileSize != 0xFFFFFFFF )
		{
			LPWSTR pszFileText;

			pszFileText = reinterpret_cast< LPWSTR > ( GlobalAlloc( GPTR, dwFileSize + 1 ) );

			if ( pszFileText )
			{
				DWORD dwRead;

				if ( ReadFile( hFile, pszFileText, dwFileSize, &dwRead, nullptr ) )
				{
					pszFileText[dwFileSize] = 0;
					if ( SetWindowText( hEdit, pszFileText ) )
					{
						bSuccess = TRUE;
					}
				}
				GlobalFree( pszFileText );
			}
		}
		CloseHandle( hFile );
	}
	return bSuccess;
}

void MainWindow::DoFileOpen( HWND hwnd )
{
	OPENFILENAME ofn;
	wchar_t szFileName[MAX_PATH] = L"";

	ZeroMemory( &ofn, sizeof( ofn ) );

	ofn.lStructSize = sizeof( ofn );
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"txt";

	if ( GetOpenFileName( &ofn ) )
	{
		HWND hEdit = GetDlgItem( hwnd, RID_MAIN_CLIENT );

		if ( LoadTextFileToEdit( hEdit, szFileName ) )
		{
			SendDlgItemMessage( mMDIFrame, RID_MAIN_STATUS, SB_SETTEXT, 0, reinterpret_cast< LPARAM >( "Opened..." ) );
			SendDlgItemMessage( mMDIFrame, RID_MAIN_STATUS, SB_SETTEXT, 1, reinterpret_cast< LPARAM >( szFileName ) );
			SetWindowText( hwnd, szFileName );
		}
	}
}

void MainWindow::DoFileSave( HWND hwnd )
{
	OPENFILENAME ofn;
	wchar_t szFileName[MAX_PATH] = L"";

	ZeroMemory( &ofn, sizeof( ofn ) );

	ofn.lStructSize = sizeof( ofn );
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*.)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = L"txt";
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

	if ( GetSaveFileName( &ofn ) )
	{
		HWND hEdit = GetDlgItem( hwnd, RID_MAIN_CLIENT );

		if ( SaveTextFileFromEdit( hEdit, szFileName ) )
		{
			SendDlgItemMessage( mMDIFrame, RID_MAIN_STATUS, SB_SETTEXT, 0, reinterpret_cast< LPARAM >( L"Saved..." ) );
			SendDlgItemMessage( mMDIFrame, RID_MAIN_STATUS, SB_SETTEXT, 1, reinterpret_cast< LPARAM >( szFileName ) );

			SetWindowText( hwnd, szFileName );
		}
	}
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

				// Create toolbar window.
				HWND hTool;
				TBBUTTON tbb[3];
				TBADDBITMAP tbab;

				hTool = CreateWindowEx(
					0,
					TOOLBARCLASSNAME,
					nullptr,
					WS_CHILD | WS_VISIBLE,
					0, 0, 0, 0,
					mMDIFrame,
					reinterpret_cast< HMENU >( RID_MAIN_TB ),
					GetModuleHandle( nullptr ),
					nullptr );

				// Send the toolbar button struct for backward compatibility.
				SendMessage( hTool, TB_BUTTONSTRUCTSIZE, reinterpret_cast< WPARAM >( sizeof( TBBUTTON ) ), 0 );

				tbab.hInst = HINST_COMMCTRL;
				tbab.nID = IDB_STD_SMALL_COLOR;
				SendMessage( hTool, TB_ADDBITMAP, 0, reinterpret_cast< LPARAM >( &tbab ) );

				ZeroMemory( &tbb, sizeof( tbb ) );
				tbb[0].iBitmap = STD_FILENEW;
				tbb[0].fsState = TBSTATE_ENABLED;
				tbb[0].fsStyle = TBSTYLE_BUTTON;
				tbb[0].idCommand = ID_FILE_NEW;

				tbb[1].iBitmap = STD_FILEOPEN;
				tbb[1].fsState = TBSTATE_ENABLED;
				tbb[1].fsStyle = TBSTYLE_BUTTON;
				tbb[1].idCommand = ID_FILE_OPEN;

				tbb[2].iBitmap = STD_FILESAVE;
				tbb[2].fsState = TBSTATE_ENABLED;
				tbb[2].fsStyle = TBSTYLE_BUTTON;
				tbb[2].idCommand = ID_FILE_OPEN;

				SendMessage( hTool, TB_ADDBUTTONS, sizeof( tbb ) / sizeof( TBBUTTON ), reinterpret_cast< LPARAM >( &tbb ) );


				// Create status Bar
				HWND hStatus;
				int statwidths[ ] = { 100, -1 };

				hStatus = CreateWindowEx(
					0,
					STATUSCLASSNAME,
					nullptr,
					WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
					0, 0, 0, 0,
					mMDIFrame,
					reinterpret_cast< HMENU >( RID_MAIN_STATUS ),
					GetModuleHandle( nullptr ),
					nullptr );

				SendMessage( hStatus, SB_SETPARTS, sizeof( statwidths ) / sizeof( int ), reinterpret_cast< LPARAM >( statwidths ) );
				SendMessage( hStatus, SB_SETTEXT, 0, reinterpret_cast< LPARAM > ( L"Message" ) );
			}
			break;
		case WM_SIZE:
			{
				HWND
					hClient,
					hTool,
					hStatus;

				RECT
					rcClient,
					rcTool,
					rcStatus;

				int
					iClientHeight,
					iToolHeight,
					iStatusHeight;

				// Size toolbar window.
				hTool = GetDlgItem( mMDIFrame, RID_MAIN_TB );
				SendMessage( hTool, TB_AUTOSIZE, 0, 0 );

				GetWindowRect( hTool, &rcTool );
				iToolHeight = rcTool.bottom - rcTool.top;

				// Size status bar window.
				hStatus = GetDlgItem( mMDIFrame, RID_MAIN_STATUS );
				SendMessage( hStatus, WM_SIZE, 0, 0 );

				GetWindowRect( hStatus, &rcStatus );
				iStatusHeight = rcStatus.bottom - rcStatus.top;

				// Calculate remaining height and size edit
				GetClientRect( mMDIFrame, &rcClient );
				iClientHeight = rcClient.bottom - iToolHeight - iStatusHeight;

				hClient = GetDlgItem( mMDIFrame, RID_MAIN_CLIENT );
				SetWindowPos( hClient, nullptr, 0, iToolHeight, rcClient.right, iClientHeight, SWP_NOZORDER );
			}
			break;
		case WM_COMMAND:
			switch ( LOWORD( wParam ) )
			{
				case ID_FILE_NEW:
					{
						CreateSubWindow( mMDIClient );
					}
					break;
				case ID_FILE_OPEN:
					{
						HWND hSub = CreateSubWindow( mMDIClient );
						if ( hSub )
						{
							DoFileOpen( hSub );
						}
					}
					break;
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
						if ( LOWORD( wParam ) >= ID_MDI_FIRSTCHILD )
						{
							return DefFrameProc( mMDIFrame, mMDIClient, WM_COMMAND, wParam, lParam );
						}
						else
						{
							HWND hChild = reinterpret_cast< HWND >( SendMessage( mMDIClient, WM_MDIGETACTIVE, 0, 0 ) );
							if ( hChild )
							{
								SendMessage( hChild, WM_COMMAND, wParam, lParam );
							}
						}
					}
					break;
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
	MDICREATESTRUCT mcs = ( ( MDICREATESTRUCT* ) ( ( CREATESTRUCT* ) lParam )->lpCreateParams )->lParam;

	switch ( uMsg )
	{
		case WM_CREATE:
			{
				HFONT hfDef;
				HWND hEdit;

				// Create edit control.
				hEdit = CreateWindowEx(
					WS_EX_CLIENTEDGE,
					L"Edit",
					L"",
					WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
					0, 0, 100, 100,
					hwnd,
					reinterpret_cast< HMENU >( RID_MAIN_CLIENT ),
					GetModuleHandle( nullptr ),
					nullptr );

				if ( !hEdit )
				{
					// Error
				}

				hfDef = reinterpret_cast< HFONT >( GetStockObject( DEFAULT_GUI_FONT );
				SendMessage( hEdit, WM_SETFONT, static_cast< WPARAM >( RID_MAIN_CLIENT ), MAKELPARAM( FALSE, 0 ) );
			}
			break;
		case WM_MDIACTIVATE:
			{
				HMENU hFileMenu;
				UINT EnableFlag;

				if ( mMDIFrame == reinterpret_cast< HWND >( LpARAM ) )
				{

				}
			}
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
