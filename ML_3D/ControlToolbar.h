#pragma once
#include "Control.h"

class Toolbar : public Control
{
public:
	void Create( HWND hwnd, LPCWSTR name, DWORD dwStyle, HMENU hmenu )
	{
		mHwnd = CreateWindowEx(
			0,
			TOOLBARCLASSNAME,
			name,
			WS_CHILD | WS_VISIBLE | dwStyle,
			0, 0, 0, 0,
			hwnd,
			hmenu,
			GetModuleHandle( nullptr ),
			nullptr );

		TESTRESULT( !mHwnd );
		//Send the toolbar button struct for backward compatibility.
		SendMessage( mHwnd, TB_BUTTONSTRUCTSIZE, static_cast< WPARAM >( sizeof( TBBUTTON ) ), 0 );
	}

	static void SetToolButton( TBBUTTON tbb[], int index, int command, int image, BYTE style, BYTE state )
	{
		tbb[index].idCommand = command;
		tbb[index].iBitmap = image;
		tbb[index].fsStyle = style;
		tbb[index].fsState = state;
	}
};