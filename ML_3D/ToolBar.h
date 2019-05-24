#pragma once
#include <Windows.h>
#include <CommCtrl.h>

class ToolBar
{
	HWND hTool;
	TBBUTTON tbb[3];
	TBADDBITMAP tbab;

public:

	HWND GetToolbar() { return hTool; }

	BOOL CreateToolbar( HWND hRoot, unsigned int RID_SB )
	{
		if ( !hTool && hRoot )
		{
			hTool = CreateWindowEx(
				0,
				TOOLBARCLASSNAME,
				nullptr,
				WS_CHILD,
				0, 0, 0, 0,
				hRoot,
				reinterpret_cast< HMENU >( RID_SB ),
				GetModuleHandle( nullptr ),
				nullptr );

			//Send the toolbar button struct for backward compatibility.
			SendMessage( hTool, TB_BUTTONSTRUCTSIZE, static_cast< WPARAM >( sizeof( TBBUTTON ) ), 0 );

			tbab.hInst = HINST_COMMCTRL;
			tbab.nID = IDB_STD_SMALL_COLOR;
			SendMessage( hTool, TB_ADDBITMAP, 0, reinterpret_cast< LPARAM >( &tbab ) );

			ZeroMemory( &tbb, sizeof( tbb ) );
			tbb[0].iBitmap = STD_FILENEW;
			tbb[0].fsState = TBSTATE_ENABLED;
			tbb[0].fsStyle = TBSTYLE_BUTTON;
			//tbb[0].idCommand = 4000;

			tbb[1].iBitmap = STD_FILEOPEN;
			tbb[1].fsState = TBSTATE_ENABLED;
			tbb[1].fsStyle = TBSTYLE_BUTTON;
			//tbb[1].idCommand = ID_FILE_OPEN;

			tbb[2].iBitmap = STD_FILESAVE;
			tbb[2].fsState = TBSTATE_ENABLED;
			tbb[2].fsStyle = TBSTYLE_BUTTON;
			//tbb[2].idCommand = ID_FILE_SAVEAS;

			SendMessage( hTool, TB_ADDBUTTONS, sizeof( tbb ) / sizeof( TBBUTTON ), reinterpret_cast< LPARAM >( &tbb ) );

			return TRUE;
		}

		return FALSE;
	}
};