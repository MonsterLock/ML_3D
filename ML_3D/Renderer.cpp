#include "Renderer.h"

Renderer::Renderer() noexcept
	:
	mHwnd( nullptr ),
	mHDC( nullptr ),
	mHRC( nullptr )
{}

void Renderer::Inititalize( HWND window, int width, int height )
{
	mHwnd = window;
	mHDC = GetDC( mHwnd );
	mOutputWidth = width;
	mOutputHeight = height;

	ZeroMemory( &mPFD, sizeof( mPFD ) );
	mPFD.nSize = sizeof( mPFD );
	mPFD.nVersion = 1;
	mPFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	mPFD.iPixelType = PFD_TYPE_RGBA;
	mPFD.cColorBits = 32;

	int pf = ChoosePixelFormat( mHDC, &mPFD );

	if( pf == 0 )
	{
		MessageBox( nullptr, L"ChoosePixelFormat() failed: Cannot find a suitable pixel format.",
					L"ERROR", MB_OK );
		return;
	}

	if( SetPixelFormat( mHDC, pf, &mPFD ) == FALSE )
	{
		MessageBox( nullptr, L"SetPixelFormat() failed: Cannot set format specified.",
					L"ERROR", MB_OK );
		return;
	}

	DescribePixelFormat( mHDC, pf, sizeof( PIXELFORMATDESCRIPTOR ), &mPFD );

	mHRC = wglCreateContext( mHDC );
	wglMakeCurrent( mHDC, mHRC );
}

void Renderer::Render()
{
	Clear();
	glBegin( GL_TRIANGLES );
	glColor3f( 1.0f, 0.0f, 0.0f );
	glVertex2i( 0, 1 );
	glColor3f( 0.0f, 1.0f, 0.0f );
	glVertex2i( -1, -1 );
	glColor3f( 0.0f, 0.0f, 1.0f );
	glVertex2i( 1, -1 );
	glEnd();
	Present();
}

void Renderer::Clear()
{
	glClear( GL_COLOR_BUFFER_BIT );
}

void Renderer::Present()
{
	glFlush();
}

void Renderer::Terminate()
{
	wglMakeCurrent( nullptr, nullptr );
	ReleaseDC( mHwnd, mHDC );
	wglDeleteContext( mHRC );
}
