#pragma once
#include <Windows.h>
#include <CommCtrl.h>

class StatusBar
{
	HWND hStatus = nullptr;
	int sbWidths[4] = {
		100,		// Command
		200,		// Project
		300,		// Window
		-1 };		// File

public:
	HWND GetStatusBar() { return hStatus; }

	BOOL CreateStatusBar( HWND hRoot, unsigned int RID_SB )
	{
		if ( !hStatus && hRoot)
		{
			hStatus = CreateWindowEx(
				0,
				STATUSCLASSNAME,
				nullptr,
				WS_CHILD | WS_VISIBLE | SBARS_TOOLTIPS,
				0, 0, 0, 0,
				hRoot,
				reinterpret_cast< HMENU >( RID_SB ),
				GetModuleHandle( nullptr ),
				nullptr );

			SendMessage( hStatus, SB_SETPARTS, sizeof( sbWidths ) / sizeof( int ), reinterpret_cast< LPARAM >( sbWidths ) );

			return TRUE;
		}
		return FALSE;
	}

	void SetText( unsigned int index, const wchar_t* text )
	{
		SendMessage( hStatus, SB_SETTEXT, index, reinterpret_cast< LPARAM > ( text ) );
	}
};