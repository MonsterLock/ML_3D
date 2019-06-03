#pragma once
#include <Windows.h>
#include <GL/gl.h>			/* OpenGL header file */
#include <GL/glu.h>			/* OpenGL utilities header file */

class RendererOGL
{
	HWND	mHwnd;
	HDC		mhDC;
	HGLRC	hRC;
	int
			m_outputWidth,
			m_outputHeight;

	void CreateDevice();
	void CreateResources();
	void OnDeviceLost();

	void Clear();
	void Present();
public:
	RendererOGL() noexcept;
	void Inititalize( HWND window, int width, int height );
	void Render();
};

