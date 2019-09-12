#pragma once
#include "GraphicsAPI.h"

class GraphicsOpenGL : public GraphicsAPI
{
protected:
	HDC						mHDC;
	HGLRC					mHRC;
	PIXELFORMATDESCRIPTOR	mPFD;
	HPALETTE				mHPALETTE;

public:
	GraphicsOpenGL() noexcept;
	void Initialize( HWND );
	void Render();
	void Clear();
	void Present();
	void Shutdown();
};

