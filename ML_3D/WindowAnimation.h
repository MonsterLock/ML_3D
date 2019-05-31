#pragma once
#include "SubWindow.h"

class WindowAnimation : public SubWindow<WindowAnimation>
{
public:
	PCWSTR ClassName() const { return L"WindowAnimation"; }
	PCWSTR WindowText() const { return L"Animation"; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};
