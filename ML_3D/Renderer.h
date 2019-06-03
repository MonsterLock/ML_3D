#pragma once
#include <Windows.h>
#include <GL/gl.h>			/* OpenGL header file */
#include <GL/glu.h>			/* OpenGL utilities header file */

class Renderer
{
protected:
	HWND					mHwnd;
	HDC						mHDC;
	HGLRC					mHRC;
	PIXELFORMATDESCRIPTOR	mPFD;
	int
							mOutputWidth,
							mOutputHeight;

public:
	Renderer() noexcept;
	void Inititalize( HWND window, int width, int height );
	void Render();
	void Clear();
	void Present();
	void Terminate();
};