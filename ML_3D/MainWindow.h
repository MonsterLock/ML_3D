#pragma once
#include "MDIWindow.h"
#include "ConsoleWindow.h"
#include "StatusBar.h"
#include "ToolBar.h"

class MainWindow : public MDIWindow<MainWindow>
{
protected:
	ConsoleWindow consoleWindow;
	StatusBar sbMain;
	ToolBar tbMain;

public:
	PCWSTR WindowText() const { return L"ML 3D Engine"; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
	BOOL GlobalCommands( UINT, WPARAM, LPARAM );

	//static LRESULT CALLBACK SubWndProc( HWND, UINT, WPARAM, LPARAM );
	//HWND CreateSubWindow( HWND hMDIClient );
	//BOOL RegSubWnd();
};