#pragma once
#include "SubWindow.h"
#include <memory>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

class SceneWindow : public SubWindow<SceneWindow>
{
	ID2D1Factory *pFactory;
	ID2D1HwndRenderTarget *pRenderTarget;
	ID2D1SolidColorBrush *pBrush;
	D2D1_ELLIPSE ellipse;

	void CalculateLayout();
	HRESULT CreateGraphicsResources();
	void DiscardGraphicsResources();
	void OnPaint();
	void Resize();

public:
	SceneWindow()
		:
		pFactory( nullptr ),
		pRenderTarget( nullptr ),
		pBrush( nullptr )
	{}

	PCWSTR WindowText() const { return L"SceneView"; }
	LRESULT HandleSubWndMessage( UINT, WPARAM, LPARAM );
};