#pragma once
#include "SubWindow.h"

class ProfilerWindow : public SubWindow<ProfilerWindow>
{
public:
	PCWSTR WindowText() const { return L"Profiler"; }
	LRESULT HandleSubWndMessage( UINT, WPARAM, LPARAM );
};

