#pragma once
#include <Windows.h>
#include "resource.h"

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

		return ( m_hwnd ? TRUE : FALSE );
	}

	HWND Window() const { return m_hwnd; }

protected:
	virtual PCWSTR ClassName() const = 0;
	virtual PCWSTR WindowText() const = 0;
	virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam ) = 0;
	HWND m_hwnd;
	HMENU m_hmenu;
	PCWSTR m_lpClassName;
	PCWSTR m_lpWindowText;
};