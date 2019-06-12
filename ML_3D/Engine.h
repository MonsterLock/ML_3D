#pragma once
#include "Editor.h"
#include "Game.h"
#include "RendererOpenGL.h"
#include "RendererD3D.h"
#include "StepTimer.h"

class Engine
{
	int mRet;
	bool
		mIsEditor,
		mIsDirectX,
		mIsRunning;
	std::shared_ptr<Mode> mMode;
	std::shared_ptr<Renderer> mRenderer;

public:
	Engine() noexcept;
	void Initialize();
	void Update();
	void Terminate();
	int Run();
};