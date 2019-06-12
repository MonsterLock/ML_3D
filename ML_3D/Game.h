#pragma once
#include "WindowMain.h"
#include "Mode.h"

class Game : public Mode
{
	friend class Engine;
	std::unique_ptr<WindowMain> mWindowMain;
	HWND mWindow;

public:
	void Initialize();
	int Update( std::shared_ptr<Renderer> );
	void Terminate();
};

