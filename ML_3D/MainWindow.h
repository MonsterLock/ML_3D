#pragma once
#include "MDIWindow.h"
#include "StatusBar.h"
#include "ToolBar.h"

class MainWindow : public MDIWindow<MainWindow>
{
protected:
	StatusBar sbMain;
	ToolBar tbMain;
	WORD mCommand;

public:
	PCWSTR WindowText() const { return mWindowText; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );

	static LRESULT CALLBACK SubWndProc( HWND, UINT, WPARAM, LPARAM );
	LRESULT HandleSubWndMessage( UINT, WPARAM, LPARAM );
	HWND CreateSubWindow( HWND hMDIClient );
	BOOL RegSubWnd();
};