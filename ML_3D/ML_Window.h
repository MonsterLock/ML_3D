#pragma once
#include <Windows.h>
#include <string>
#include <Commctrl.h>
#include "resource.h"
#define ID_MDI_FIRSTCHILD 50000
static HWND m_MDIClient;

template <class DERIVED_TYPE>
class ML_Window
{
public:
	ML_Window()
		:
		m_hwnd( nullptr ),
		m_lpClassName( nullptr ),
		m_lpWindowText( nullptr )
	{}
	hwnd CreateNewWin( HWND hMDIClient )
	{
		MIDCREATESTRUCT mcs;
		HWND hChild;

		mcs.szTitle = "[Untitled]";
		mcs.szClass = g_szChildClassName;
		mcs.hOwner = GetModuleHandle( NULL );
		mcs.x = mcs.cx = CW_USEDEFAULT;
		mcs.y = mcs.cy = CW_USEDEFAULT;
		mcs.style = MDIS_ALLCHILDSTYLES;

		hChild = reinterpret_cast< HWND >( SendMessage( hMDIClient, WM_MDICREATE, 0, reinterpret_cast< LONG >( &mcs ) ) );

		if ( !hChild )
		{
			MessageBox( hMDIClient, "Sub-window Creation Failed.", "ERROR",
						MB_ICONEXCLAMATION | MB_OK );
		}
		return hChild;
	}

	static LRESULT CALLBACK WndProc(
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam
	)
	{
		switch ( msg )
		{
			case WM_CREATE:
				{
					CLIENTCREATESTRUCT ccs;

					// Create MDI Client

					// Find window menu where children will be listed
					ccs.hWindowMenu = GetSubMenu( GetMenu( hwnd ), 2 );
					ccs.idFirstChild = ID_MDI_FIRSTCHILD;

					m_MDIClient = CreateWindowEx(
						WS_EX_CLIENTEDGE,
						"mdiclient",
						NULL,
						WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE,
						CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
						hwnd,
						( HMENU ) IDC_MAIN_MDI,
						GetModuleHandle( NULL ),
						( LPVOID ) &ccs );

					if ( !m_MDIClient )
						MessageBox( hwnd, "Could not create MDI client.", "Error", MB_OK | MB_ICONERROR );
				}
				break;
			case WM_CLOSE:
				DestroyWindow( hwnd );
				break;
			case WM_DESTROY:
				PostQuitMessage( 0 );
				break;
			case WM_COMMAND:
				switch ( LOWORD( wParam ) )
				{
					case ID_WINDOW_TILE:
						SendMessage( m_MDIClient, WM_MDITILE, 0, 0 );
						break;
					case ID_WINDOW_CASCADE:
						SendMessage( m_MDIClient, WM_MDICASCADE, 0, 0 );
						break;
					default:
						{
							if ( LOWORD( wParam ) >= ID_MDI_FIRSTCHILD )
							{
								DefFrameProc( hwnd, m_MDIClient, WM_COMMAND, wParam, lParam );
							}
							else
							{
								HWND hChild = ( HWND ) SendMessage( m_MDIClient, WM_MDIGETACTIVE, 0, 0 );
								if ( hChild )
								{
									SendMessage( hChild, WM_COMMAND, wParam, lParam );
								}
							}
						}
				}
				break;
			default:
				return DefFrameProc( hwnd, m_MDIClient, msg, wParam, lParam );
		}
		return 0;
	}

	static LRESULT CALLBACK MDIChildWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		switch ( msg )
		{
			case WM_CREATE:
				{
					HFONT hfDefault;
					HWND hEdit;

					// Create Edit Control

					hEdit = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", "",
											WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
											0, 0, 100, 100, hwnd, ( HMENU ) IDC_CHILD_EDIT, GetModuleHandle( NULL ), NULL );
					if ( hEdit == NULL )
						MessageBox( hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR );

					hfDefault = ( HFONT ) GetStockObject( DEFAULT_GUI_FONT );
					SendMessage( hEdit, WM_SETFONT, ( WPARAM ) hfDefault, MAKELPARAM( FALSE, 0 ) );
				}
				break;
			case WM_MDIACTIVATE:
				{
					HMENU hMenu, hFileMenu;
					UINT EnableFlag;

					hMenu = GetMenu( g_hMainWindow );
					if ( hwnd == ( HWND ) lParam )
					{	   //being activated, enable the menus
						EnableFlag = MF_ENABLED;
					}
					else
					{						   //being de-activated, gray the menus
						EnableFlag = MF_GRAYED;
					}

					EnableMenuItem( hMenu, 1, MF_BYPOSITION | EnableFlag );
					EnableMenuItem( hMenu, 2, MF_BYPOSITION | EnableFlag );

					hFileMenu = GetSubMenu( hMenu, 0 );
					EnableMenuItem( hFileMenu, ID_FILE_SAVEAS, MF_BYCOMMAND | EnableFlag );

					EnableMenuItem( hFileMenu, ID_FILE_CLOSE, MF_BYCOMMAND | EnableFlag );
					EnableMenuItem( hFileMenu, ID_FILE_CLOSEALL, MF_BYCOMMAND | EnableFlag );

					DrawMenuBar( g_hMainWindow );
				}
				break;
			case WM_COMMAND:
				switch ( LOWORD( wParam ) )
				{
					case ID_FILE_OPEN:
						DoFileOpen( hwnd );
						break;
					case ID_FILE_SAVEAS:
						DoFileSave( hwnd );
						break;
					case ID_EDIT_CUT:
						SendDlgItemMessage( hwnd, IDC_CHILD_EDIT, WM_CUT, 0, 0 );
						break;
					case ID_EDIT_COPY:
						SendDlgItemMessage( hwnd, IDC_CHILD_EDIT, WM_COPY, 0, 0 );
						break;
					case ID_EDIT_PASTE:
						SendDlgItemMessage( hwnd, IDC_CHILD_EDIT, WM_PASTE, 0, 0 );
						break;
				}
				break;
			case WM_SIZE:
				{
					HWND hEdit;
					RECT rcClient;

					// Calculate remaining height and size edit

					GetClientRect( hwnd, &rcClient );

					hEdit = GetDlgItem( hwnd, IDC_CHILD_EDIT );
					SetWindowPos( hEdit, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER );
				}
				return DefMDIChildProc( hwnd, msg, wParam, lParam );
			default:
				return DefMDIChildProc( hwnd, msg, wParam, lParam );

		}
		return 0;
	}

	BOOL SetUpMDIChildWindowClass( HINSTANCE hInstance )
	{
		WNDCLASSEX wc;

		wc.cbSize = sizeof( WNDCLASSEX );
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = MDIChildWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
		wc.hCursor = LoadCursor( NULL, IDC_ARROW );
		wc.hbrBackground = ( HBRUSH ) ( COLOR_3DFACE );
		wc.lpszMenuName = NULL;
		wc.lpszClassName = L"MDIChildWindow";
		wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );

		if ( !RegisterClassEx( &wc ) )
		{
			MessageBox( 0, "Could Not Register Child Window", "Oh Oh...",
						MB_ICONEXCLAMATION | MB_OK );
			return FALSE;
		}
		else
			return TRUE;
	}

	virtual BOOL Create(
		PCWSTR lpClassName,
		PCWSTR lpWindowName,
		LPWSTR lpMenuName,
		DWORD dwStyle,
		DWORD dwExStyle = 0,
		int x = CW_USEDEFAULT,
		int y = CW_USEDEFAULT,
		int nWidth = CW_USEDEFAULT,
		int nHeight = CW_USEDEFAULT,
		HWND hWndParent = 0,
		HMENU  hMenu = 0 )
	{
		m_lpClassName = lpClassName;
		m_lpWindowText = lpWindowName;

		// Register the window class.
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof( WNDCLASSEX );
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = DERIVED_TYPE::WndProc;
		wc.hInstance = GetModuleHandle( nullptr );
		wc.hIcon = static_cast< HICON >(
			LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 32, 32, 0 ) );
		wc.hbrBackground = reinterpret_cast< HBRUSH >( COLOR_WINDOW );
		wc.lpszMenuName = lpMenuName;
		wc.lpszClassName = ClassName();
		wc.hIconSm = static_cast< HICON >(
			LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 16, 16, 0 ) );

		if ( !RegisterClassEx( &wc ) )
		{
			MessageBox( nullptr, L"Window registration failed.", L"Error", MB_OK | MB_ICONERROR );
			return FALSE;
		}

		if ( !CreateMDIChildWindowClass() )
		{
			return 0;
		}

		// Create the window.
		m_hwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,					// Optional window styles.
			ClassName(),						// Window class
			WindowText(),						// Window text
			dwStyle,							// Window style
			x, y, nWidth, nHeight,				// Size and position
			hWndParent,							// Parent window
			hMenu,								// Menu
			GetModuleHandle( nullptr ),			// Instance handle
			this );								// Additional application data

		// Save the menu
		m_hmenu = GetMenu( m_hwnd );

		if ( !m_hwnd )
		{
			MessageBox( nullptr, L"Window creation failed.", L"Error", MB_OK | MB_ICONERROR );
			return FALSE;
		}

		m_MDIClient = m_hwnd;

		return ( m_hwnd ? TRUE : FALSE );
	}
	HWND m_hwnd;
	HMENU m_hmenu;
	PCWSTR
		m_lpClassName,
		m_lpWindowText;
};