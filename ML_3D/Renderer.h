#pragma once
#include "Global.h"

class Renderer
{
protected:
	HWND		mHwnd;
	int
		mOutputWidth,
		mOutputHeight;

	virtual void Clear() = 0;
	virtual void Present() = 0;

public:
	Renderer() noexcept
		:
		mHwnd( nullptr )
	{}
	virtual void Initialize( HWND window ) = 0;
	virtual void Render() = 0;
	virtual void Terminate() = 0;
};