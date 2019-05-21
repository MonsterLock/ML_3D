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
	BOOL CreateStatusBar( HWND hRoot, unsigned int RID_SB )
	{
		if ( !hStatus )
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

			SendMessage( hStatus, SB_SETPARTS, 4, reinterpret_cast< LPARAM >( sbWidths ) );
			SendMessage( hStatus, SB_SETTEXT, 0, reinterpret_cast< LPARAM > ( L"Welcome" ) );
			SendMessage( hStatus, SB_SETTEXT, 1, reinterpret_cast< LPARAM > ( L"" ) );
			SendMessage( hStatus, SB_SETTEXT, 2, reinterpret_cast< LPARAM > ( L"Start Page" ) );

			return TRUE;
		}
		return FALSE;
	}

	HWND GetSBHandle() { return hStatus; }
};