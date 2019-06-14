#pragma once
#include "Global.h"

class GraphicsAPI
{
protected:
	HWND mHwnd;
	int
		mOutputWidth,
		mOutputHeight;
	float
		mScreenDepth,
		mScreenNear;

	virtual void Clear() = 0;
	virtual void Present() = 0;

public:
	GraphicsAPI() noexcept
		:
		mHwnd( nullptr ),
		mScreenDepth( 1000.0f ),
		mScreenNear( 0.1f )
	{}
	virtual void Initialize( HWND window ) = 0;
	virtual void Render() = 0;
	virtual void Terminate() = 0;
};