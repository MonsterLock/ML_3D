#pragma once
#include "SubWindow.h"
class ConsoleWindow : public SubWindow<ConsoleWindow>
{
public:
	PCWSTR WindowText() const { return L"Console"; }
	LRESULT HandleSubWndMessage( UINT, WPARAM, LPARAM );
	void ToggleWindow( int,  int );
};