#pragma once
#include <Windows.h>
#include "resource.h"

#define ID_MDI_FIRSTCHILD 50000

template <class DERIVED_TYPE>
class MDIWindow
{
public:
	MDIWindow()
		:
		mMDIFrame( nullptr ),
		mMDIClient( nullptr ),
		m_lpFrameName( nullptr ),
		m_lpWindowText( nullptr )
	{}

	virtual ~MDIWindow()
	{
		if ( !mMDIFrame )
		{
			delete mMDIFrame;
		}
		if ( !mMDIClient )
		{
			delete mMDIClient;
		}
	}

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
			return DefFrameProc( hwnd, nullptr, uMsg, wParam, lParam );
		}
	}

	virtual BOOL Create( PCWSTR lpWindowName )
	{
		m_lpFrameName = L"MDIFRAME";
		m_lpWindowText = lpWindowName;

		// Register the frame window class.
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof( WNDCLASSEX );
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.style = CS_PARENTDC | CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.lpszClassName = ClassName();
		wc.lpszMenuName = MAKEINTRESOURCE( IDR_MAIN_MENU );
		wc.hInstance = GetModuleHandle( nullptr );
		wc.hbrBackground = CreateSolidBrush(RGB(0, 255, 0)); // Client window didn't render if green shows.
		wc.hCursor = LoadCursor( nullptr, IDC_ARROW );
		wc.hIcon = static_cast< HICON >(
			LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 32, 32, 0 ) );
		wc.hIconSm = static_cast< HICON >(
			LoadImage( wc.hInstance, MAKEINTRESOURCE( IDI_ML_LOGO ), IMAGE_ICON, 16, 16, 0 ) );

		if ( !RegisterClassEx( &wc ) )
		{
			MessageBox( nullptr, L"Registering Frame Window Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
			return FALSE;
		}

		// Create the frame window.
		mMDIFrame = CreateWindowEx(
			WS_EX_APPWINDOW | WS_EX_CONTROLPARENT,							// Optional window styles.
			ClassName(),													// Window class
			WindowText(),													// Window text
			WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE,				// Window style
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,		// Size and position
			nullptr,														// Parent window
			nullptr,														// Menu
			GetModuleHandle( nullptr ),										// Instance handle
			this );															// Additional application data

		if ( !mMDIFrame )
		{
			MessageBox( nullptr, L"Creating Frame Window Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
			return FALSE;
		}

		mMenu = GetMenu( mMDIFrame );

		// Create the client window.
		CLIENTCREATESTRUCT ccs;
		ccs.hWindowMenu = GetSubMenu( mMenu, 5 );
		ccs.idFirstChild = ID_MDI_FIRSTCHILD;
		SetClientColor( CreateSolidBrush( RGB( 255, 0, 255 ) ) );

		mMDIClient = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			clientClass,
			nullptr,
			WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			mMDIFrame,
			0,
			GetModuleHandle( nullptr ),
			&ccs );

		if ( !mMDIClient )
		{
			MessageBox( nullptr, L"Creating Client Window Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
			return FALSE;
		}

		return TRUE;
	}

	HWND FrameWnd() const { return mMDIFrame; }
	HWND ClientWnd() const { return mMDIClient; }
	void SetClientColor( HBRUSH color ) { mClientColor = color; }
	HBRUSH GetClientColor() const { return mClientColor; }

protected:
	virtual PCWSTR WindowText() const = 0;
	virtual PCWSTR ClassName() const = 0;
	virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam ) = 0;

	const LPCTSTR clientClass = L"MDICLIENT";
	HMENU mMenu;
	HBRUSH mClientColor;
	HWND
		mMDIFrame,
		mMDIClient;
	PCWSTR
		m_lpFrameName,
		m_lpWindowText;
};

//CreateSolidBrush(RGB(0, 0, 0));