#pragma once
#include "GraphicsD3D.h"
#include "GraphicsOpenGL.h"
#include "Camera.h"
#include "Model.h"
#include "Shader.h"
#include "Light.h"

class RenderEngine
{
	bool
		mIsDirectX,
		mIsFullScreen,
		mIsVsyncEnabled;

	std::shared_ptr<GraphicsD3D> mGraphics;
	std::shared_ptr<Camera> mCamera;
	std::shared_ptr<Model> mModel;
	std::shared_ptr<Shader> mShader;
	std::shared_ptr<Light> mLight;

public:
	RenderEngine() noexcept;

	void Initialize( HWND targetWindow );
	void Terminate();
	void Frame();
	void Render( float );
};