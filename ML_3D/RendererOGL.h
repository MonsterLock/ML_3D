#pragma once
//#include "Global.h"
#include "Renderer.h"

class RendererOGL : public Renderer
{
protected:
	HDC						mHDC;
	HGLRC					mHRC;
	PIXELFORMATDESCRIPTOR	mPFD;
	HPALETTE				mHPALETTE;

public:
	RendererOGL() noexcept;
	BOOL Initialize( HWND window, int width, int height );
	void Render();
	void Clear();
	void Present();
	void Terminate();
};

