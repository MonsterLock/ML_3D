#pragma once
#include "Renderer.h"

class RendererOpenGL : public Renderer
{
protected:
	HDC						mHDC;
	HGLRC					mHRC;
	PIXELFORMATDESCRIPTOR	mPFD;
	HPALETTE				mHPALETTE;

public:
	RendererOpenGL() noexcept;
	void Initialize( HWND );
	void Render();
	void Clear();
	void Present();
	void Terminate();
};

