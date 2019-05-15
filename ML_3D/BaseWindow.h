#pragma once
#include <Windows.h>
#include "resource.h"
#define ID_MDI_FIRSTCHILD 50000

template <class DERIVED_TYPE>
class BaseWindow
{
public:
	static LRESULT CALLBACK WndProc(
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam )
	{
		DERIVED_TYPE* pThis = nullptr;

		switch ( uMsg )
		{
			case WM_NCCREATE:
				{
					CREATESTRUCT* pCreate = reinterpret_cast< CREATESTRUCT* >( lParam );
					pThis = reinterpret_cast< DERIVED_TYPE* >( pCreate->lpCreateParams );
					SetWindowLongPtr( hwnd, GWLP_USERDATA, reinterpret_cast< LONG_PTR >( pThis ) );
					pThis->m_hwnd = hwnd;
				}
				break;
			default:
				{
					pThis = reinterpret_cast< DERIVED_TYPE* >( GetWindowLongPtr( hwnd, GWLP_USERDATA ) );
				}
				break;
		}
		if ( pThis )
		{
			return pThis->HandleMessage( uMsg, wParam, lParam );
		}
		else
		{
			return DefFrameProc( hwnd, 0, uMsg, wParam, lParam );
		}
	}

	static LRESULT CALLBACK MDIWndProc(
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam )
	{
		switch ( uMsg )
		{
			case WM_SIZE:
				{
					RECT rcClient;

					// Calculate the remaining height and size edit.

					GetClientRect( hwnd, &rcClient );
					SetWindowPos( nullptr, nullptr, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER );
				}
				return DefMDIChildProc( hwnd, uMsg, wParam, lParam );
			default: return DefMDIChildProc( hwnd, uMsg, wParam, lParam );
		}

		return 0;
	}

	BaseWindow()
		:
		m_hwnd( nullptr ),
		m_lpClassName( nullptr ),
		m_lpWindowText( nullptr )
	{}

	virtual ~BaseWindow()
	{
		if ( !m_hwnd )
		{
			delete m_hwnd;
		}
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

		// Register the frame.
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof( WNDCLASSEX );
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = DERIVED_TYPE::WndProc;
		wc.hInstance = GetModuleHandle( nullptr );
		wc.hIcon = static_cast< HICON >(
			LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 32, 32, 0 ) );
		wc.lpszMenuName = lpMenuName;
		wc.lpszClassName = ClassName();
		wc.hIconSm = static_cast< HICON >(
			LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 16, 16, 0 ) );

		if ( !RegisterClassEx( &wc ) )
		{
			MessageBox( nullptr, L"Registering Frame Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
			return FALSE;
		}

		// Register the MDI.
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = DERIVED_TYPE::MDIWndProc;
		wc.lpszMenuName = reinterpret_cast< LPCTSTR > ( nullptr );
		wc.cbWndExtra = 0;
		wc.lpszClassName = L"MDICLIENT";

		if ( !RegisterClassEx( &wc ) )
		{
			MessageBox( nullptr, L"Registering MDI Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
			return FALSE;
		}

		// Create the frame.
		m_hwnd = CreateWindowEx(
			dwExStyle,							// Optional window styles.
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

//		// Create the MDI.
		CLIENTCREATESTRUCT ccs;

		// Retrieve the handle to the window menu and assign the first sub-window identifier.
		ccs.hWindowMenu = GetSubMenu( m_hmenu, 5 );
		ccs.idFirstChild = ID_MDI_FIRSTCHILD;

		m_hMDIwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"MDICLIENT",
			reinterpret_cast< LPCTSTR >( nullptr ),
			WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			m_hwnd,
			nullptr,
			GetModuleHandle( nullptr ),
			reinterpret_cast< LPSTR >( &ccs ) );

		ShowWindow( m_hMDIwnd, SW_SHOW );

		return ( m_hwnd ? TRUE : FALSE );
	}

	HWND Window() const { return m_hwnd; }
	HWND MDIWnd() const { return m_hMDIwnd; }


protected:
	virtual PCWSTR ClassName() const = 0;
	virtual PCWSTR WindowText() const = 0;
	virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam ) = 0;
	HWND m_hwnd;
	HWND m_hMDIwnd;
	HMENU m_hmenu;
	PCWSTR m_lpClassName;
	PCWSTR m_lpWindowText;
};