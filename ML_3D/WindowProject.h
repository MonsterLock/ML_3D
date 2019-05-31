#pragma once
#include "SubWindow.h"

class WindowProject : public SubWindow< WindowProject>
{
public:
	PCWSTR ClassName() const { return L"WindowProject"; }
	PCWSTR WindowText() const { return L"Project"; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};
