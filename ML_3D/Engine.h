#pragma once
#include "MainWindow.h"
#include "RendererOGL.h"
#include "RendererD3D.h"
#include "Editor.h"

class Engine
{
	int mRet;
	std::unique_ptr<Editor> mEditor;
	Renderer* mRenderer;

public:
	Engine() noexcept;
	void Initialize();
	void Update();
	void Terminate();
	int Run();
};