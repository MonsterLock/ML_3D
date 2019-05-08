#pragma once
#include "BaseWindow.h"

class MainWindow : public BaseWindow<MainWindow>
{
public:
	PCWSTR ClassName() const;
	PCWSTR WindowText() const;
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};