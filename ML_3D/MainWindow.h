#pragma once
#include "MDIWindow.h"
#include "AnimationWindow.h"
#include "ConsoleWindow.h"
#include "GameWindow.h"
#include "HierarchyWindow.h"
#include "InformationWindow.h"
#include "LightingWindow.h"
#include "ProfilerWindow.h"
#include "ProjectWindow.h"
#include "SceneWindow.h"
#include "StatusBar.h"
#include "TabControl.h"
#include "ToolBar.h"

class MainWindow : public MDIWindow<MainWindow>
{
protected:
	AnimationWindow animationWindow;
	ConsoleWindow consoleWindow;
	GameWindow gameWindow;
	HierarchyWindow hierarchyWindow;
	InformationWindow informationWindow;
	LightingWindow lightingWindow;
	ProfilerWindow profilerWindow;
	ProjectWindow projectWindow;
	SceneWindow sceneWindow;
	StatusBar sbMain;
	ToolBar tbMain;

	TabControl
		tabView,
		tabProperties,
		tabInfo;

	HWND
		currentViewWnd = nullptr,
		currentInfoWnd = nullptr,
		currentCategoryWnd = nullptr,
		currentPropertiesWnd = nullptr;
	HFONT hf;

	BOOL GlobalCommands( UINT, WPARAM, LPARAM );
	static BOOL CALLBACK SetFont( HWND, LPARAM );
	HWND ViewPanel( int );
	HWND InfoPanel( int );
	HWND PropertiesPanel( int );
	HWND CategoryPanel( int );
	void ChangeTabs( HWND&, HWND& );
	void CallSize();

	static BOOL CALLBACK AboutDlg( HWND, UINT, WPARAM, LPARAM );
public:
	PCWSTR WindowText() const { return L"ML 3D Engine"; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};