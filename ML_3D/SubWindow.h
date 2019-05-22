#pragma once
#include <Windows.h>

template <class DERIVED_TYPE>
class SubWindow
{
protected:
	virtual LRESULT HandleSubWndMessage( UINT, WPARAM, LPARAM ) = 0;
	virtual PCWSTR WindowText() const = 0;

	HWND mSubWnd,
		mParent;

	PCWSTR mSubWindowClass;

public:
	SubWindow()
		:
		mSubWnd( nullptr ),
		mParent( nullptr )
	{}

	static LRESULT CALLBACK SubWndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
	{
		DERIVED_TYPE* pThis = nullptr;

		switch ( uMsg )
		{
			case WM_NCCREATE:
				{
					CREATESTRUCT* pCreate = reinterpret_cast< CREATESTRUCT* > ( lParam );
					MDICREATESTRUCT* pMDICreate = reinterpret_cast< MDICREATESTRUCT* > ( pCreate->lpCreateParams );
					pThis = reinterpret_cast< DERIVED_TYPE* >( pMDICreate->lParam );
					SetWindowLongPtr( hwnd, GWLP_USERDATA, reinterpret_cast< LONG_PTR >( pThis ) );
					pThis->mSubWnd = hwnd;
				}
				break;
			default:
				{
					pThis = reinterpret_cast< DERIVED_TYPE* >( GetWindowLongPtr( hwnd, GWLP_USERDATA ) );
				}
		}
		if ( pThis )
		{
			return pThis->HandleSubWndMessage( uMsg, wParam, lParam );
		}
		else
		{
			return  DefMDIChildProc( hwnd, uMsg, wParam, lParam );
		}
		return  DefMDIChildProc( hwnd, uMsg, wParam, lParam );
	}

	BOOL RegSubWnd(
		PCWSTR lpWindowClass,
		DWORD dwStyle,
		HICON rIcon,
		DWORD dwExStyle = WS_EX_MDICHILD,
		int x = CW_USEDEFAULT,
		int y = CW_USEDEFAULT,
		int nWidth = CW_USEDEFAULT,
		int nHeight = CW_USEDEFAULT,
		HWND hWndParent = 0,
		HMENU hMenu = 0 )
	{
		mSubWindowClass = lpWindowClass;

		// Register the sub-window class
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof( WNDCLASSEX );
		wc.style = dwStyle;
		wc.lpfnWndProc = SubWndProc;
		wc.lpszClassName = ClassName();
		wc.lpszMenuName = nullptr;
		wc.hInstance = GetModuleHandle( nullptr );
		wc.hbrBackground = reinterpret_cast< HBRUSH > ( COLOR_WINDOWFRAME );
		wc.hIconSm = rIcon;

		if ( !RegisterClassEx( &wc ) )
		{
			MessageBox( nullptr, L"Registering Sub-window Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
			return FALSE;
		}
		return TRUE;
	}

	BOOL CreateSubWnd(
		HWND hParent,
		DWORD dwStyle,
		int x, int y,
		int width, int height )
	{
		mParent = hParent;

		MDICREATESTRUCT mcs;
		mcs.szTitle = WindowText();
		mcs.szClass = ClassName();
		mcs.hOwner = GetModuleHandle( nullptr );
		mcs.x = x;
		mcs.y = y;
		mcs.cx = width;
		mcs.cy = height;
		mcs.style = dwStyle;
		mcs.lParam = reinterpret_cast< LPARAM >( this );

		mSubWnd = reinterpret_cast< HWND >( SendMessage( hParent, WM_MDICREATE, 0, reinterpret_cast< LONG >( &mcs ) ) );

		if ( !mSubWnd )
		{
			MessageBox( hParent, L"Creating Sub-window failed.", L"ERROR", MB_ICONEXCLAMATION | MB_OK );
			return FALSE;
		}

		return TRUE;
	}

	HWND HSubWnd() const { return mSubWnd; }
	PCWSTR ClassName() const { return mSubWindowClass; }
};

//HWND MainWindow::CreateSubWindow( HWND hwnd )
//{
//	HWND hSub;
//
//	MDICREATESTRUCT mcs;
//	mcs.szTitle = L"[Untitled]";
//	mcs.szClass = L"TestSubWnd";
//	mcs.hOwner = GetModuleHandle( nullptr );
//	mcs.x = mcs.cx = CW_USEDEFAULT;
//	mcs.y = mcs.cy = CW_USEDEFAULT;
//	mcs.style = MDIS_ALLCHILDSTYLES;
//
//	hSub = reinterpret_cast< HWND >(
//		SendMessage( hwnd, WM_MDICREATE, 0, reinterpret_cast< LONG >( &mcs ) ) );
//
//	if ( !hSub )
//	{
//		MessageBox( hwnd, L"Sub-window creation failed.", L"ERROR",
//					MB_ICONEXCLAMATION | MB_OK );
//	}
//
//	return hSub;
//}
//
//BOOL MainWindow::RegSubWnd()
//{
//	WNDCLASSEX wc = { 0 };
//	wc.cbSize = sizeof( WNDCLASSEX );
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.lpfnWndProc = SubWndProc;
//	wc.lpszClassName = L"TestSubWnd";
//	wc.lpszMenuName = nullptr;
//	wc.hInstance = GetModuleHandle( nullptr );
//	wc.hbrBackground = reinterpret_cast< HBRUSH > ( COLOR_WINDOWFRAME );
//	wc.hIconSm = LoadIcon( nullptr, IDI_WINLOGO );
//
//	return RegisterClassEx( &wc ) ? TRUE : FALSE;
//}