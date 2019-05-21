#pragma once
#include "MDIWindow.h"
#include "StatusBar.h"

class MainWindow : public MDIWindow<MainWindow>
{
protected:
	StatusBar sbMain;

	void OnQuit();
	void OnAbout();
	BOOL LoadTextFileToEdit( HWND hEdit, LPCWSTR pszFileName );
	BOOL SaveTextFileFromEdit( HWND hEdit, LPCWSTR pszFileName );
	void DoFileOpen( HWND hwnd );
	void DoFileSave( HWND hwnd );

public:
	PCWSTR WindowText() const { return mWindowText; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
	static BOOL CALLBACK AboutDlgProc( HWND, UINT, WPARAM, LPARAM );

	static LRESULT CALLBACK SubWndProc( HWND, UINT, WPARAM, LPARAM );
	LRESULT HandleSubWndMessage( UINT, WPARAM, LPARAM );
	HWND CreateSubWindow( HWND hMDIClient );
	BOOL RegSubWnd();
};