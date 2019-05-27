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
	HWND ViewPanel( int index );
	HWND InfoPanel( int index );
	HWND PropertiesPanel( int index );
	HWND CategoryPanel( int index );
	void ChangeTabs( HWND& currentTab, HWND& newTab );
	void CallSize();
public:
	PCWSTR WindowText() const { return L"ML 3D Engine"; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};