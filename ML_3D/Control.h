#pragma once
#include "Global.h"

class Control
{
protected:
	HWND mHwnd;

public:
	Control() noexcept
		:
		mHwnd( nullptr )
	{}

	HWND Wnd() { return mHwnd; };

	virtual BOOL Create( HWND hwnd, LPCWSTR name, DWORD dwStyle, HMENU hmenu ) = 0;
};