#pragma once
#include "WindowMessenger.h"
#include "MainWindow.h"
#include "RendererOGL.h"
#include "RendererD3D.h"
#include <fbxsdk.h>
#include <shobjidl.h>
//#include <glad/glad.h>

#define ISD3DRENDERER 0

class Engine
{
	int mRet;
	std::unique_ptr<MainWindow> mMainWindow;
	Renderer* mRenderer;
	HACCEL mHAccel;

public:
	Engine() noexcept;
	void Initialize();
	void Update();
	void Terminate();
	int Run();
};

