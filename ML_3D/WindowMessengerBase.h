#pragma once
#include <Windows.h>
#include "resource.h"

template <class DERIVED_TYPE>
class WindowMessengerBase
{
protected:
	HWND mHwnd;
	HMENU mMenu;

	virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam ) = 0;

public:
	WindowMessengerBase() noexcept
		:
		mHwnd( nullptr )
	{}

	HWND Wnd() const { return mHwnd; }
	virtual PCWSTR ClassName() const = 0;

	static LRESULT CALLBACK WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
	{
		DERIVED_TYPE* pThis = nullptr;

		switch( uMsg )
		{
			case WM_NCCREATE:
				{
					pThis = reinterpret_cast< DERIVED_TYPE* >( reinterpret_cast< CREATESTRUCT* > ( lParam )->lpCreateParams );
					SetWindowLongPtr( hwnd, GWLP_USERDATA, reinterpret_cast< LONG_PTR >( pThis ) );

					pThis->mHwnd = hwnd;
				}
				break;
			default:
				pThis = reinterpret_cast< DERIVED_TYPE* >( GetWindowLongPtr( hwnd, GWLP_USERDATA ) );
				break;
		}
		if( pThis )
			return pThis->HandleMessage( uMsg, wParam, lParam );
		else
			return  DefWindowProc( hwnd, uMsg, wParam, lParam );
	}

	virtual BOOL Create()
	{
		// Register the message window class.
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof( WNDCLASSEX );
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.style = 0;
		wc.lpfnWndProc = WndProc;
		wc.lpszClassName = ClassName();
		wc.hInstance = GetModuleHandle( nullptr );

		if( !RegisterClassEx( &wc ) )
		{
			MessageBox( nullptr, L"Registering Message Window Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
			return FALSE;
		}

		// Create the message window.
		mHwnd = CreateWindowEx(
			WS_EX_APPWINDOW,												// Optional window styles.
			ClassName(),													// Window class
			L" ",															// Window text
			0,																// Window style
			0, 0, 0, 0,														// Size and position
			HWND_MESSAGE,													// Parent window
			nullptr,														// Menu
			GetModuleHandle( nullptr ),										// Instance handle
			this );															// Additional application data

		if( !mHwnd )
		{
			MessageBox( nullptr, L"Creating Message Window Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
			return FALSE;
		}

		return TRUE;
	}
};