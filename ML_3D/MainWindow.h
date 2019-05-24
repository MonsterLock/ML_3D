#pragma once
#include "MDIWindow.h"
#include "SceneWindow.h"
#include "ConsoleWindow.h"
#include "StatusBar.h"
#include "ToolBar.h"
#include "TabControl.h"

class MainWindow : public MDIWindow<MainWindow>
{
protected:
	SceneWindow sceneWindow;
	ConsoleWindow consoleWindow;
	StatusBar sbMain;
	ToolBar tbMain;
	TabControl
		tabMain,
		tabProperties,
		tabInfo;

	//HWND
	//	tabMain,
	//	tabProperties, tabInfo;

	BOOL GlobalCommands( UINT, WPARAM, LPARAM );
	void ToggleWindow( HWND, int, int );
	void CallSize();
public:
	PCWSTR WindowText() const { return L"ML 3D Engine"; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};