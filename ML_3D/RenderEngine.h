#pragma once
#include "GraphicsD3D.h"
#include "GraphicsOpenGL.h"
#include "Camera.h"
#include "Model.h"
#include "TextureShader.h"
#include "Light.h"
#include "Bitmap.h"
#include "Text.h"

class RenderEngine
{
	bool
		mIsDirectX,
		mIsFullScreen,
		mIsVsyncEnabled;

	std::shared_ptr<GraphicsD3D> mGraphics;
	std::shared_ptr<Camera> mCamera;
	std::shared_ptr<Text> mText;

public:
	RenderEngine() noexcept;

	void Initialize( HWND targetWindow );
	void Shutdown();
	void Frame();
	void Render( float );
};