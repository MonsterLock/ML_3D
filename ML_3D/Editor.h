#pragma once
#include "AppMode.h"
#include "WindowEditor.h"

class Editor : public AppMode
{
	std::shared_ptr<WindowEditor> mWindowEditor;
	HACCEL mHAccel;

public:
	Editor() noexcept;
	void Initialize();
	void Update();
	void Terminate();
};
