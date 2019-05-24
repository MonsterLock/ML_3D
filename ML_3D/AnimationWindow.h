#pragma once
#include "SubWindow.h"

class AnimationWindow : public SubWindow<AnimationWindow>
{
public:
	PCWSTR WindowText() const { return L"AnimationView"; }
	LRESULT HandleSubWndMessage( UINT, WPARAM, LPARAM );
};

