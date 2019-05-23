#pragma once
#include <Windows.h>
#include "resource.h"

template <class DERIVED_TYPE>
class SubWindow
{
protected:
	virtual LRESULT HandleSubWndMessage( UINT, WPARAM, LPARAM ) = 0;
	virtual PCWSTR WindowText() const = 0;

	HWND mSubWnd;
	PCWSTR mSubWindowClass;

public:
	SubWindow()
		:
		mSubWnd( nullptr )
	{}

	static LRESULT CALLBACK SubWndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
	{
		DERIVED_TYPE* pThis = nullptr;

		switch( uMsg )
		{
			case WM_NCCREATE:
				{
					pThis = reinterpret_cast< DERIVED_TYPE* >( ( reinterpret_cast< MDICREATESTRUCT* > ( (
						reinterpret_cast< CREATESTRUCT* > ( lParam ) )->lpCreateParams ) )->lParam );
					SetWindowLongPtr( hwnd, GWLP_USERDATA, reinterpret_cast< LONG_PTR >( pThis ) );
					pThis->mSubWnd = hwnd;
				}
				break;
			default:
				{
					pThis = reinterpret_cast< DERIVED_TYPE* >( GetWindowLongPtr( hwnd, GWLP_USERDATA ) );
				}
		}
		if( pThis )
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
		HICON rIcon )
	{
		mSubWindowClass = lpWindowClass;

		// Register the sub-window class
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof( WNDCLASSEX );
		wc.lpfnWndProc = SubWndProc;
		wc.lpszClassName = ClassName();
		wc.lpszMenuName = nullptr;
		wc.hInstance = GetModuleHandle( nullptr );
		wc.hbrBackground = reinterpret_cast< HBRUSH > ( COLOR_BACKGROUND );
		wc.style = CS_VREDRAW | CS_HREDRAW | dwStyle;
		wc.hIconSm = rIcon;

		if( !RegisterClassEx( &wc ) )
		{
			MessageBox( nullptr, L"Registering Sub-window Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
			return FALSE;
		}
		return TRUE;
	}

	BOOL CreateSubWnd(
		HWND hParent,
		DWORD dwStyle )
	{
		MDICREATESTRUCT mcs;
		mcs.szClass = ClassName();
		mcs.szTitle = WindowText();
		mcs.hOwner = GetModuleHandle( nullptr );
		mcs.x = mcs.cx = CW_USEDEFAULT;
		mcs.y = mcs.cy = CW_USEDEFAULT;
		mcs.style = MDIS_ALLCHILDSTYLES  | dwStyle;
		mcs.lParam = reinterpret_cast< LPARAM >( this );

		mSubWnd = reinterpret_cast< HWND >( SendMessage( hParent, WM_MDICREATE, 0, reinterpret_cast< LONG >( &mcs ) ) );

		if( !mSubWnd )
		{
			MessageBox( hParent, L"Creating Sub-window failed.", L"ERROR", MB_ICONEXCLAMATION | MB_OK );
			return FALSE;
		}

		return TRUE;
	}

	HWND HSubWnd() const { return mSubWnd; }
	PCWSTR ClassName() const { return mSubWindowClass; }
};
