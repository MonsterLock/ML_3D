#pragma once
#include "SubWindow.h"

class WindowProperties : public SubWindow< WindowProperties>
{
public:
	PCWSTR ClassName() const { return L"WindowProperties"; }
	PCWSTR WindowText() const { return L"Information"; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};

