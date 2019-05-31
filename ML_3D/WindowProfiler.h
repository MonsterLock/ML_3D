#pragma once
#include "SubWindow.h"

class WindowProfiler : public SubWindow<WindowProfiler>
{
public:
	PCWSTR ClassName() const { return L"WindowProfiler"; }
	PCWSTR WindowText() const { return L"Profiler"; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};
