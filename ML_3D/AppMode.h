#pragma once
#include "Global.h"
#include "RenderEngine.h"
#include "Input.h"

class AppMode
{
protected:
	std::unique_ptr<RenderEngine> mRenderEngine;
	std::unique_ptr<Input> mInput;

	HWND mRenderWindow;
	int mMsg;

public:
	AppMode() noexcept : mRenderWindow( nullptr ){}
	virtual ~AppMode() { if( mRenderWindow ) mRenderWindow = nullptr; }
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Terminate() = 0;
	HWND GetRenderWnd() { return mRenderWindow; }
	int GetMsg() { return mMsg; }
};

