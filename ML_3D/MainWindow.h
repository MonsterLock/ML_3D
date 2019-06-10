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
	enum UIWindows { Scene, Game, Anim, Proj, Console, Prof, Prop, Light, Hier, NumberOfWindows };
	enum UITabControls { ViewTab, InfoTab, PropTab, NumberOfTabControls };

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
	Tab					tabMain[NumberOfTabControls];
	HFONT				hf;
	int					currentTab[NumberOfTabControls];

	BOOL GlobalCommands( UINT, WPARAM, LPARAM );
	static BOOL CALLBACK SetFont( HWND, LPARAM );
	HWND WindowIndex( int );
	void CallSize();
	void TogglePanel( int index );
	static BOOL CALLBACK AboutDlg( HWND, UINT, WPARAM, LPARAM );

public:
	PCWSTR WindowText() const { return L"ML 3D Engine"; }
	HWND RenderWnd() { return WindowIndex( currentTab[ViewTab] ); }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};