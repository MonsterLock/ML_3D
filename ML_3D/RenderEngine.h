#pragma once
#include "Global.h"
#include "GraphicsD3D.h"
#include "GraphicsOpenGL.h"

class RenderEngine
{
	bool
		mIsDirectX,
		mIsFullScreen,
		mIsVsyncEnabled;
	float
		mScreenDepth,
		mScreenNear;

	std::shared_ptr<GraphicsAPI> mGraphics;
public:
	RenderEngine() noexcept;
	RenderEngine( const RenderEngine& );
	~RenderEngine();

	void Initialize();
	void Terminate();
	void Frame();
	void Render();
};