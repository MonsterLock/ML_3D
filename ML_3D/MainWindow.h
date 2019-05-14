#pragma once
#include "BaseWindow.h"

class MainWindow : public BaseWindow<MainWindow>
{
protected:
	void OnQuit();
	void OnAbout();
public:
	PCWSTR ClassName() const;
	PCWSTR WindowText() const;
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
	static BOOL CALLBACK AboutDlgProc( HWND, UINT, WPARAM, LPARAM );
};