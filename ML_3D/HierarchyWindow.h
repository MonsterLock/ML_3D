#pragma once
#include "SubWindow.h"
class HierarchyWindow :
	public SubWindow< HierarchyWindow>
{
public:
	PCWSTR WindowText() const { return L"Hierarchy"; }
	LRESULT HandleSubWndMessage( UINT, WPARAM, LPARAM );
};

