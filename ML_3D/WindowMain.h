#pragma once
#include "WindowBase.h"
class WindowMain : public WindowBase<WindowMain>
{
public:
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};

