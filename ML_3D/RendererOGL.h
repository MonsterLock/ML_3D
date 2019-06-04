#pragma once
#include "Renderer.h"
#include <GL/gl.h>			/* OpenGL header file */
#include <GL/glu.h>			/* OpenGL utilities header file */

class RendererOGL : public Renderer
{
protected:
	HDC						mHDC;
	HGLRC					mHRC;
	PIXELFORMATDESCRIPTOR	mPFD;
	HPALETTE				mHPALETTE;

public:
	RendererOGL() noexcept;
	BOOL Inititalize( HWND window, int width, int height );
	void Render();
	void Clear();
	void Present();
	void Terminate();
};

