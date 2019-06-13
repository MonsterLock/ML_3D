#pragma once
#include "Global.h"

template <class DERIVED_TYPE>
class WindowBase
{
protected:
	HWND mHwnd;

public:
	WindowBase() : mHwnd( nullptr ) {}
	virtual PCWSTR ClassName() const { return L"Main"; }
	virtual PCWSTR WindowText() const { return L"ML 3D"; };
	virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam ) = 0;
	HWND Wnd() const { return mHwnd; }

	static LRESULT CALLBACK WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
	{
		DERIVED_TYPE *pThis = nullptr;

		if( uMsg == WM_NCCREATE )
		{
			pThis = reinterpret_cast< DERIVED_TYPE* >(
				( reinterpret_cast< CREATESTRUCT* >( lParam ) )->lpCreateParams );
			SetWindowLongPtr( hwnd, GWLP_USERDATA, ( LONG_PTR )pThis );

			pThis->mHwnd = hwnd;

			TESTRESULT( !pThis->mHwnd );
		}
		else
		{
			pThis = reinterpret_cast< DERIVED_TYPE* >( GetWindowLongPtr( hwnd, GWLP_USERDATA ) );
		}
		if( pThis )
		{
			return pThis->HandleMessage( uMsg, wParam, lParam );
		}
		else
		{
			return DefWindowProc( hwnd, uMsg, wParam, lParam );
		}
	}

	virtual void Create()
	{
		// Register the main window class.
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof( WNDCLASSEX );
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.lpszClassName = ClassName();
		//wc.lpszMenuName = MAKEINTRESOURCE( IDR_MAIN_MENU );
		wc.hInstance = GetModuleHandle( nullptr );
		wc.hbrBackground = reinterpret_cast< HBRUSH >( COLOR_ACTIVEBORDER );
		wc.hCursor = LoadCursor( nullptr, IDC_ARROW );
		wc.hIcon = static_cast< HICON >(
			LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 32, 32, 0 ) );
		wc.hIconSm = static_cast< HICON >(
			LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 16, 16, 0 ) );

		TESTRESULT( !RegisterClassEx( &wc ) );

		// Create the frame window.
		mHwnd = CreateWindowEx(
			WS_EX_APPWINDOW,												// Optional window styles.
			ClassName(),													// Window class
			WindowText(),													// Window text
			WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE,				// Window style
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,		// Size and position
			nullptr,														// Parent window
			nullptr,														// Menu
			GetModuleHandle( nullptr ),										// Instance handle
			this );															// Additional application data

		TESTRESULT( !mHwnd );

		ShowWindow( mHwnd, SW_SHOWNORMAL | SW_MAXIMIZE );
	}
};
