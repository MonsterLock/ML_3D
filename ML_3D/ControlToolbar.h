#pragma once
#include "Control.h"

class Toolbar : public Control
{
public:
	BOOL Create( HWND hwnd, LPCWSTR name, DWORD dwStyle, HMENU hmenu )
	{
		if ( !mHwnd && hwnd )
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

			//Send the toolbar button struct for backward compatibility.
			SendMessage( mHwnd, TB_BUTTONSTRUCTSIZE, static_cast< WPARAM >( sizeof( TBBUTTON ) ), 0 );

			return TRUE;
		}
		REPORTMSG( Create(), nullptr, Create() failed to pass a valid HWND in parameters or toolbar has already been created. );
		return FALSE;
	}

	static void SetToolButton( TBBUTTON tbb[], int index, int command, int image, BYTE style, BYTE state )
	{
		tbb[index].idCommand = command;
		tbb[index].iBitmap = image;
		tbb[index].fsStyle = style;
		tbb[index].fsState = state;
	}
};