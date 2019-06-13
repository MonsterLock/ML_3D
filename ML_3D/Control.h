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

	virtual void Create( HWND hwnd, LPCWSTR name, DWORD dwStyle, HMENU hmenu ) = 0;
};