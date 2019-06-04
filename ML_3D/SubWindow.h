#pragma once
#include "ReportMessage.h"
#include "resource.h"

template <class DERIVED_TYPE>
class SubWindow
{
protected:
	HWND mHwnd;

	virtual LRESULT HandleMessage( UINT, WPARAM, LPARAM ) = 0;
	virtual PCWSTR WindowText() const = 0;

public:
	SubWindow()
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
					pThis = reinterpret_cast< DERIVED_TYPE* >( ( reinterpret_cast< MDICREATESTRUCT* > ( (
						reinterpret_cast< CREATESTRUCT* > ( lParam ) )->lpCreateParams ) )->lParam );
					SetWindowLongPtr( hwnd, GWLP_USERDATA, reinterpret_cast< LONG_PTR >( pThis ) );
					pThis->mHwnd = hwnd;

					if( !pThis->mHwnd )
					{
						REPORTMSG( SetWindowLongPtr(), nullptr, SetWindowLongPtr() failed to assign pThis->mHwnd a valid HWND. );
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
			return  DefMDIChildProc( hwnd, uMsg, wParam, lParam );

		return  DefMDIChildProc( hwnd, uMsg, wParam, lParam );
	}

	BOOL RegSubWnd(
		DWORD dwStyle,
		HICON rIcon )
	{
		// Register the sub-window class
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof( WNDCLASSEX );
		wc.lpfnWndProc = WndProc;
		wc.lpszClassName = ClassName();
		wc.lpszMenuName = nullptr;
		wc.hInstance = GetModuleHandle( nullptr );
		wc.hbrBackground = reinterpret_cast< HBRUSH >( COLOR_APPWORKSPACE );
		wc.style = CS_VREDRAW | CS_HREDRAW | dwStyle;
		wc.hIconSm = rIcon;

		if( !RegisterClassEx( &wc ) )
		{
			REPORTMSG( RegisterClassEx(), false, RegisterClassEx() failed to register WNDCLASSEX wc. );
			return FALSE;
		}
		return TRUE;
	}

	HWND CreateSubWnd(
		HWND hParent,
		DWORD dwStyle )
	{
		MDICREATESTRUCT mcs;
		mcs.szClass = ClassName();
		mcs.szTitle = WindowText();
		mcs.hOwner = GetModuleHandle( nullptr );
		mcs.x = mcs.cx = CW_USEDEFAULT;
		mcs.y = mcs.cy = CW_USEDEFAULT;
		mcs.style = MDIS_ALLCHILDSTYLES | dwStyle;
		mcs.lParam = reinterpret_cast< LPARAM >( this );

		mHwnd = reinterpret_cast< HWND >( SendMessage( hParent, WM_MDICREATE, 0, reinterpret_cast< LONG >( &mcs ) ) );

		if( !mHwnd )
		{
			REPORTMSG( SendMessage(), nullptr, SendMessage() failed to assign mHwnd a valid HWND. );
		}

		return Wnd();
	}
};
