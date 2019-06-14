#pragma once
#include "Editor.h"
#include "Game.h"

class Engine
{
	std::shared_ptr<AppMode> mApp;
	bool
		mIsEditor,
		mIsRunning;

public:
	Engine() noexcept;
	void Initialize();
	void Update();
	void Terminate();
	int Run();
};