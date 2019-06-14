#pragma once
#include "GraphicsD3D.h"
#include "GraphicsOpenGL.h"

class RenderEngine
{
	bool
		mIsDirectX,
		mIsFullScreen,
		mIsVsyncEnabled;

	std::shared_ptr<GraphicsAPI> mGraphics;
public:
	RenderEngine() noexcept;
	RenderEngine( const RenderEngine& ) noexcept;
	~RenderEngine();

	void Initialize( HWND targetWindow );
	void Terminate();
	void Frame();
	void Render();
};