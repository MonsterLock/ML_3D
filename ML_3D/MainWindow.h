#pragma once
#include "MDIWindow.h"

class MainWindow : public MDIWindow<MainWindow>
{
protected:
	void OnQuit();
	void OnAbout();

	BOOL LoadTextFileToEdit( HWND hEdit, LPCWSTR pszFileName );
	BOOL SaveTextFileFromEdit( HWND hEdit, LPCWSTR pszFileName );
	void DoFileOpen( HWND hwnd );
	void DoFileSave( HWND hwnd );

public:
	PCWSTR WindowText() const { return mWindowText; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
	BOOL RegisterMDIChild(const HBRUSH);
	static BOOL CALLBACK AboutDlgProc( HWND, UINT, WPARAM, LPARAM );

	static LRESULT CALLBACK SubWndProc( HWND, UINT, WPARAM, LPARAM );
	HWND CreateSubWindow( HWND hMDIClient );
	BOOL RegSubWnd();
};