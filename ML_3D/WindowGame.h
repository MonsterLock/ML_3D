#pragma once
#include "SubWindow.h"

class WindowGame : public SubWindow<WindowGame>
{
public:
	PCWSTR ClassName() const { return L"WindowGame"; }
	PCWSTR WindowText() const { return L"Game"; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};
