#pragma once
#include <Windows.h>
#include "resource.h"

template <class DERIVED_TYPE>
class MDIWindow
{
protected:
	virtual PCWSTR WindowText() const = 0;
	virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam ) = 0;

	const PCWSTR
		mFrameClass = L"MDIFRAME",
		mClientClass = L"MDICLIENT";
	HWND
		mMDIFrame,
		mMDIClient;
	HMENU mMenu;

public:
	MDIWindow()
		:
		mMDIFrame( nullptr ),
		mMDIClient( nullptr )
	{}

	static LRESULT CALLBACK WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
	{
		DERIVED_TYPE* pThis = nullptr;

		switch( uMsg )
		{
			case WM_NCCREATE:
				{
					pThis = reinterpret_cast< DERIVED_TYPE* >(
						( reinterpret_cast< CREATESTRUCT* >( lParam ) )->lpCreateParams );
					SetWindowLongPtr( hwnd, GWLP_USERDATA, reinterpret_cast< LONG_PTR >( pThis ) );
					pThis->mMDIFrame = hwnd;
					pThis->mMenu = GetMenu( hwnd );

					// Create the client window.
					CLIENTCREATESTRUCT ccs;
					ccs.hWindowMenu = GetSubMenu( pThis->mMenu, 0 );
					ccs.idFirstChild = ID_MDI_FIRSTCHILD;

					pThis->mMDIClient = CreateWindowEx(
						0,
						pThis->mClientClass,
						nullptr,
						MDIS_ALLCHILDSTYLES | WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
						0, 0, 0, 0,
						pThis->mMDIFrame,
						reinterpret_cast< HMENU >( RID_MAIN_CLIENT ),
						GetModuleHandle( nullptr ),
						&ccs );

					if( !pThis->mMDIClient )
					{
						MessageBox( nullptr, L"Creating Client Window Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
						return FALSE;
					}
				}
				break;
			default:
				pThis = reinterpret_cast< DERIVED_TYPE* >( GetWindowLongPtr( hwnd, GWLP_USERDATA ) );
				break;
		}
		if( pThis )
			return pThis->HandleMessage( uMsg, wParam, lParam );
		else
			return DefFrameProc( hwnd, nullptr, uMsg, wParam, lParam );
	}

	virtual BOOL Create()
	{
		// Register the frame window class.
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof( WNDCLASSEX );
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.style = CS_PARENTDC | CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.lpszClassName = mFrameClass;
		wc.lpszMenuName = MAKEINTRESOURCE( IDR_MAIN_MENU );
		wc.hInstance = GetModuleHandle( nullptr );
		wc.hbrBackground = CreateSolidBrush( RGB( 0, 255, 0 ) ); // Client window didn't render if green shows.
		wc.hCursor = LoadCursor( nullptr, IDC_ARROW );
		wc.hIcon = static_cast< HICON >(
			LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 32, 32, 0 ) );
		wc.hIconSm = static_cast< HICON >(
			LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 16, 16, 0 ) );

		if( !RegisterClassEx( &wc ) )
		{
			MessageBox( nullptr, L"Registering Frame Window Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
			return FALSE;
		}

		// Create the frame window.
		mMDIFrame = CreateWindowEx(
			WS_EX_APPWINDOW,												// Optional window styles.
			mFrameClass,													// Window class
			WindowText(),													// Window text
			WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE,				// Window style
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,		// Size and position
			nullptr,														// Parent window
			nullptr,														// Menu
			GetModuleHandle( nullptr ),										// Instance handle
			this );															// Additional application data

		if( !mMDIFrame )
		{
			MessageBox( nullptr, L"Creating Frame Window Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
			return FALSE;
		}

		ShowWindow( mMDIFrame, SW_SHOWNORMAL | SW_MAXIMIZE );

		return TRUE;
	}

	HWND FrameWnd() const { return mMDIFrame; }
	HWND ClientWnd() const { return mMDIClient; }
	HMENU MainMenu() { return mMenu; }
};

//CreateSolidBrush(RGB(0, 0, 0));