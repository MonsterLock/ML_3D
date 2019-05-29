#pragma once
#include "SubWindow.h"

class ProjectWindow : public SubWindow< ProjectWindow>
{
public:
	PCWSTR WindowText() const { return L"Project"; }
	LRESULT HandleSubWndMessage( UINT, WPARAM, LPARAM );
};
