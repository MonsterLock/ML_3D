#pragma once
#include "WindowEditor.h"

class Editor
{
	std::shared_ptr<WindowEditor> mWindowEditor;
	HACCEL mHAccel;
	std::unique_ptr<RenderEngine> mRenderEngine;

	HWND mRenderWindow;
	int mMsg;
public:
	Editor() noexcept;
	void Initialize();
	void Update();
	void Shutdown();
};
