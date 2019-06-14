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

class WindowEditor : public MDIWindow<WindowEditor>
{
protected:
	enum UIWindows { Scene, Game, Anim, Proj, Console, Prof, Prop, Light, Hier, NumWindows };
	enum UITabControls { ViewTab, InfoTab, PropTab, NumTabControls };

	WindowAnimation		mAnimation;
	WindowConsole		mConsole;
	WindowGame			mGame;
	WindowHierarchy		mHierarchy;
	WindowLighting		mLighting;
	WindowProfiler		mProfiler;
	WindowProject		mProject;
	WindowProperties	mProperties;
	WindowScene			mScene;
	Statusbar			mStatusbar;
	Toolbar				mToolbar;
	Tab					mTabs[NumTabControls];
	HFONT				mHFONT;
	int					mCurrentTab[NumTabControls];

	BOOL GlobalCommands( UINT, WPARAM, LPARAM );
	static BOOL CALLBACK SetFont( HWND, LPARAM );
	HWND WindowIndex( int );
	void CallSize();
	void TogglePanel( int );
	static BOOL CALLBACK AboutDlg( HWND, UINT, WPARAM, LPARAM );

public:
	WindowEditor() noexcept;
	PCWSTR WindowText() const { return L"ML 3D Engine"; }
	HWND RenderWnd() { return WindowIndex( mCurrentTab[ViewTab] ); }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};