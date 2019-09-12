#pragma once
#include "WindowMain.h"
#include "Input.h"

class Game
{
	std::shared_ptr<WindowMain> mWindowMain;
	std::shared_ptr<Input> m_input;
	std::unique_ptr<RenderEngine> mRenderEngine;

	HWND mRenderWindow;
	int mMsg;

public:
	Game( ) noexcept;
	void Initialize();
	void Update();
	void Shutdown();
	void ProcessInput( );
};
