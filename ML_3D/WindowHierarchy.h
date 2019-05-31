#pragma once
#include "SubWindow.h"

class WindowHierarchy : public SubWindow< WindowHierarchy>
{
public:
	PCWSTR ClassName() const { return L"WindowHierarchy"; }
	PCWSTR WindowText() const { return L"Hierarchy"; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};
