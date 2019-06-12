#pragma once
#include "Global.h"
#include "Renderer.h"

class Mode
{
	friend class Engine;

protected:
	HWND mRender;
	bool mIsMsgReceived;

public:
	Mode()
		:
		mRender( nullptr )
	{}
	virtual ~Mode()
	{
		if( mRender ) mRender = nullptr;
	}
	virtual void Initialize() = 0;
	virtual int Update( std::shared_ptr<Renderer> ) = 0;
	virtual void Terminate() = 0;
	HWND GetRenderWnd() { return mRender; }
	bool IsMsgReceived() { return mIsMsgReceived; }
};

