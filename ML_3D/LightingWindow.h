#pragma once
#include "SubWindow.h"

class LightingWindow : public SubWindow<LightingWindow>
{
public:
	PCWSTR WindowText() const { return L"Lighting"; }
	LRESULT HandleSubWndMessage( UINT, WPARAM, LPARAM );
};

