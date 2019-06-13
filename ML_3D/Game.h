#pragma once
#include "AppMode.h"
#include "WindowMain.h"

class Game : public AppMode
{
	std::shared_ptr<WindowMain> mWindowMain;

public:
	void Initialize();
	void Update();
	void Terminate();
};
