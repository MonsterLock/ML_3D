#pragma once
#include "Control.h"

class Tab : public Control
{
public:
	void Create( HWND hwnd, LPCWSTR name, DWORD dwStyle, HMENU hmenu )
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

		TESTRESULT( !mHwnd );
	}

	void AddTab( int index, TCITEM tab, LPCWSTR title )
	{
		tab.pszText = const_cast< LPWSTR >( title );
		TabCtrl_InsertItem( mHwnd, index, &tab );
	}
};