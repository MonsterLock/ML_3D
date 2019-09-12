#pragma once
#include "RenderEngine.h"
#include "Input.h"

class Engine
{
	RenderEngine* mRender;
	Input* mInput;

public:
	Engine() noexcept;
	void Initialize();
	void Shutdown();
};