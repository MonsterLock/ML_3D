#pragma once
#include "SubWindow.h"

class GameWindow : public SubWindow<GameWindow>
{
public:
	PCWSTR WindowText() const { return L"GameView"; }
	LRESULT HandleSubWndMessage( UINT, WPARAM, LPARAM );
};

