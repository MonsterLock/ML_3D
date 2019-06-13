#pragma once
#include "Editor.h"
#include "Game.h"

class Engine
{
	int mRet;
	bool
		mIsEditor,
		mIsRunning;
	std::shared_ptr<AppMode> mApp;

public:
	Engine() noexcept;
	void Initialize();
	void Update();
	void Terminate();
	int Run();
};