#pragma once
#include "Manager.h"
#include "MainWindow.h"

class Editor :
	public Manager
{
	friend class Engine;
	std::unique_ptr<MainWindow> mMainWindow;
	HACCEL mHAccel;
	MSG* mMSG;

public:
	Editor() noexcept;
	virtual BOOL Initialize();
	virtual void Update();
	virtual void Terminate();
};
