#pragma once
#include "MDIWindow.h"
#include "WindowAnimation.h"
#include "WindowConsole.h"
#include "WindowGame.h"
#include "WindowHierarchy.h"
#include "WindowLighting.h"
#include "WindowProfiler.h"
#include "WindowProject.h"
#include "WindowProperties.h"
#include "WindowScene.h"
#include "ControlStatusBar.h"
#include "ControlTab.h"
#include "ControlToolBar.h"

class MainWindow : public MDIWindow<MainWindow>
{
protected:
	WindowAnimation		animationWnd;
	WindowConsole		consoleWnd;
	WindowGame			gameWnd;
	WindowHierarchy		hierarchyWnd;
	WindowLighting		lightingWnd;
	WindowProfiler		profilerWnd;
	WindowProject		projectWnd;
	WindowProperties	propertiesWnd;
	WindowScene			sceneWnd;
	Statusbar			sbMain;
	Toolbar				tbMain;
	Tab
						tabView,
						tabProperties,
						tabInfo;
	HWND
						currentViewWnd,
						currentInfoWnd,
						currentCategoryWnd,
						currentPropertiesWnd;
	HFONT				hf;

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
	HWND RenderWnd() const { return currentViewWnd; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};