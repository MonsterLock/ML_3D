#pragma once
#include "BaseWindow.h"

class MainWindow : public BaseWindow<MainWindow>
{
protected:
	HWND m_hMDIwnd;
	void OnQuit();
	void OnAbout();
public:
	HWND MDIWnd() const { return m_hMDIwnd; }
	PCWSTR ClassName() const;
	PCWSTR WindowText() const;
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
	static BOOL CALLBACK AboutDlgProc( HWND, UINT, WPARAM, LPARAM );
	static LRESULT CALLBACK MDIWndProc( HWND, UINT, WPARAM, LPARAM );
};