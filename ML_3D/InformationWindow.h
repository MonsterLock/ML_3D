#pragma once
#include "SubWindow.h"

class InformationWindow : public SubWindow< InformationWindow>
{
public:
	PCWSTR WindowText() const { return L"Information"; }
	LRESULT HandleSubWndMessage( UINT, WPARAM, LPARAM );
};

