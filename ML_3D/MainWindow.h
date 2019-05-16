#pragma once
#include "BaseWindow.h"

class MainWindow : public BaseWindow<MainWindow>
{
protected:
	HBRUSH mClientColor;
	void OnQuit();
	void OnAbout();
public:
	HWND ClientWnd() const { return mMDIClient; }
	PCWSTR ClassName() const;
	PCWSTR WindowText() const;
	void SetClientColor( const HBRUSH color );
	HBRUSH GetClientColor() const;
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
	BOOL RegisterMDI(const HBRUSH);
	static BOOL CALLBACK AboutDlgProc( HWND, UINT, WPARAM, LPARAM );
	static LRESULT CALLBACK MDIWndProc( HWND, UINT, WPARAM, LPARAM );
};