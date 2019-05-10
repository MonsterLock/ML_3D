#pragma once
#include "BaseWindow.h"

class MainWindow : public BaseWindow<MainWindow>
{
protected:
	void OnQuit();
public:
	PCWSTR ClassName() const;
	PCWSTR WindowText() const;
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};