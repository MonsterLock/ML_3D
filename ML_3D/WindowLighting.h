#pragma once
#include "SubWindow.h"

class WindowLighting : public SubWindow<WindowLighting>
{
public:
	PCWSTR ClassName() const { return L"WindowLighting"; }
	PCWSTR WindowText() const { return L"Lighting"; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};
