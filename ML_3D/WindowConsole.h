#pragma once
#include "SubWindow.h"

class WindowConsole : public SubWindow<WindowConsole>
{
public:
	PCWSTR ClassName() const { return L"WindowConsole"; }
	PCWSTR WindowText() const { return L"Console"; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};