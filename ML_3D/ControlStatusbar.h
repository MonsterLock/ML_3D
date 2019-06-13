#pragma once
#include "Control.h"

class Statusbar : public Control
{
	int sbWidths[4] = {
		100,		// Command
		200,		// Project
		300,		// Window
		-1 };		// File

public:
	void Create( HWND hwnd, LPCWSTR name, DWORD dwStyle, HMENU hmenu )
	{
		mHwnd = CreateWindowEx(
			0,
			STATUSCLASSNAME,
			name,
			WS_CHILD | WS_VISIBLE | SBARS_TOOLTIPS | dwStyle,
			0, 0, 0, 0,
			hwnd,
			hmenu,
			GetModuleHandle( nullptr ),
			nullptr );

		TESTRESULT( !mHwnd );

		SendMessage( Wnd(), SB_SETPARTS, sizeof( sbWidths ) / sizeof( int ), reinterpret_cast< LPARAM >( sbWidths ) );
	}

	void SetText( unsigned int index, const wchar_t* text )
	{
		SendMessage( Wnd(), SB_SETTEXT, index, reinterpret_cast< LPARAM > ( text ) );
	}
};