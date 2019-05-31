#pragma once
#include "Control.h"

class Tab : public Control
{
public:
	BOOL Create( HWND hwnd, LPCWSTR name, DWORD dwStyle, HMENU hmenu )
	{
		if( !mHwnd && hwnd )
		{
			mHwnd = CreateWindowEx(
				0,
				WC_TABCONTROL,
				name,
				WS_CHILD | WS_VISIBLE | dwStyle,
				0, 0, 0, 0,
				hwnd,
				hmenu,
				GetModuleHandle( nullptr ),
				nullptr );

			return TRUE;
		}
		MessageBox( nullptr, L"Could not create tab control.", L"ERROR", MB_OK | MB_ICONERROR );
		return FALSE;
	}

	void AddTab( int index, TCITEM tab, LPCWSTR title )
	{
		tab.pszText = const_cast< LPWSTR >( title );
		TabCtrl_InsertItem( mHwnd, index, &tab );
	}
};