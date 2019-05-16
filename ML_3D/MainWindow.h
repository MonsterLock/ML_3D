#pragma once
#include "MDIWindow.h"

class MainWindow : public MDIWindow<MainWindow>
{
protected:
	void OnQuit();
	void OnAbout();

public:
	PCWSTR WindowText() const { return mWindowText; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
	BOOL RegisterMDIChild(const HBRUSH);
	static BOOL CALLBACK AboutDlgProc( HWND, UINT, WPARAM, LPARAM );
	static LRESULT CALLBACK MDIWndProc( HWND, UINT, WPARAM, LPARAM );
};