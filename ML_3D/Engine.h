#pragma once
#include "MainWindow.h"

class Engine
{
	MainWindow win;

public:
	Engine();
	~Engine();
	BOOL Run();
	BOOL Init();
	BOOL Release();
};

