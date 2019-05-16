#pragma once
#include <Windows.h>
#include "resource.h"

template <class DERIVED_TYPE>
class BaseWindow
{
public:
	static LRESULT CALLBACK WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
	{
		DERIVED_TYPE* pThis = nullptr;

		switch ( uMsg )
		{
			case WM_NCCREATE:
				{
					CREATESTRUCT* pCreate = reinterpret_cast< CREATESTRUCT* >( lParam );
					pThis = reinterpret_cast< DERIVED_TYPE* >( pCreate->lpCreateParams );
					SetWindowLongPtr( hwnd, GWLP_USERDATA, reinterpret_cast< LONG_PTR >( pThis ) );
					pThis->mMDIFrame = hwnd;
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
			return DefWindowProc( hwnd, uMsg, wParam, lParam );
		}
	}

	BaseWindow()
		:
		mMDIFrame( nullptr ),
		m_lpClassName( nullptr ),
		m_lpWindowText( nullptr )
	{}

	virtual ~BaseWindow()
	{
		if ( !mMDIFrame )
		{
			delete mMDIFrame;
		}
	}

	virtual BOOL Create(
		PCWSTR lpClassName,
		PCWSTR lpWindowName,
		DWORD dwStyle,
		LPWSTR lpMenuName = nullptr,
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
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.style = CS_PARENTDC | CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
		wc.lpszClassName = ClassName();
		wc.lpszMenuName = MAKEINTRESOURCE( IDR_MAIN_MENU );
		wc.hInstance = GetModuleHandle( nullptr );
		wc.hCursor = LoadCursor( NULL, IDC_ARROW );
		wc.hbrBackground = reinterpret_cast< HBRUSH >( COLOR_APPWORKSPACE + 1 );
		wc.hIcon = static_cast< HICON >(
			LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 32, 32, 0 ) );
		wc.hIconSm = static_cast< HICON >(
			LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 16, 16, 0 ) );

		if ( !RegisterClassEx( &wc ) )
		{
			MessageBox( nullptr, L"Registering Frame Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
			return FALSE;
		}

		// Create the frame.
		mMDIFrame = CreateWindowEx(
			WS_EX_APPWINDOW | WS_EX_CONTROLPARENT,		// Optional window styles.
			ClassName(),								// Window class
			WindowText(),								// Window text
			dwStyle,									// Window style
			x, y, nWidth, nHeight,						// Size and position
			nullptr,									// Parent window
			nullptr,									// Menu
			GetModuleHandle( nullptr ),					// Instance handle
			this );										// Additional application data

		if ( !mMDIFrame )
		{
			MessageBox( nullptr, L"Creating Frame Window Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
			return FALSE;
		}
		return ( mMDIFrame ? TRUE : FALSE );
	}

	HWND FrameWnd() const { return mMDIFrame; }

protected:
	virtual PCWSTR ClassName() const = 0;
	virtual PCWSTR WindowText() const = 0;
	virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam ) = 0;
	HWND mMDIFrame;
	PCWSTR m_lpClassName;
	PCWSTR m_lpWindowText;
};