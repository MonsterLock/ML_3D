#pragma once
#include "SubWindow.h"

class WindowScene : public SubWindow<WindowScene>
{

public:
	PCWSTR ClassName() const { return L"WindowScene"; }
	PCWSTR WindowText() const { return L"Scene"; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};
