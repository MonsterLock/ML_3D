#pragma once
#include "SubWindow.h"

class SceneWindow : public SubWindow<SceneWindow>
{
public:
	PCWSTR WindowText() const { return L"SceneView"; }
	LRESULT HandleSubWndMessage( UINT, WPARAM, LPARAM );
};