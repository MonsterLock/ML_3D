#pragma once
#include "AppMode.h"
#include "WindowMain.h"
#include "Input.h"

class Game : public AppMode
{
	std::shared_ptr<WindowMain> mWindowMain;
	std::shared_ptr<Input> m_input;

public:
	void Initialize();
	void Update();
	void Terminate();
	void ProcessInput( );
};
