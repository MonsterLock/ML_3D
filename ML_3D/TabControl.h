#pragma once
#include <Windows.h>
#include <CommCtrl.h>

class TabControl
{
	HWND hTab;
public:
	HWND GetTabControl() { return hTab; }

	BOOL CreateTabs( HWND hRoot, DWORD dwStyle, LPCWSTR tabName )
	{
		if( !hTab && hRoot )
		{
			hTab = CreateWindowEx(
				0,
				WC_TABCONTROL,
				tabName,
				WS_CHILD | WS_VISIBLE | dwStyle,
				0, 0, 0, 0,
				hRoot,
				nullptr,
				GetModuleHandle( nullptr ),
				nullptr );

			return TRUE;
		}

		return FALSE;
	}
};