#include "RendererOGL.h"

void RendererOGL::CreateDevice()
{ return; }

void RendererOGL::CreateResources()
{ return; }

void RendererOGL::OnDeviceLost()
{ return; }

void RendererOGL::Clear()
{ glClear( GL_COLOR_BUFFER_BIT ); }

void RendererOGL::Present()
{ return; }

RendererOGL::RendererOGL() noexcept
{}

void RendererOGL::Inititalize( HWND window, int width, int height )
{
	mHwnd = window;
	m_outputWidth = width;
	m_outputHeight = height;

	int pf;
	HDC hDC;
	PIXELFORMATDESCRIPTOR pfd;

	hDC = GetDC( window );
	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;

	pf = ChoosePixelFormat( hDC, &pfd );

	if( pf == 0 )
	{
		MessageBox( nullptr, L"ChoosePixelFormat() failed: " "Cannot find a suitable pixel format.", L"ERROR", MB_OK );
		return;
	}

	if( !SetPixelFormat( hDC, pf, &pfd) )
	{
		MessageBox( nullptr, L"SetPixelFormat() failed: " "Cannot set format specified.", L"ERROR", MB_OK );
		return;
	}

	DescribePixelFormat( hDC, pf, sizeof( PIXELFORMATDESCRIPTOR ), &pfd );

	ReleaseDC( window, hDC );
}

void RendererOGL::Render()
{
	/* rotate a triangle around */
	Clear();
	{
		glBegin( GL_TRIANGLES );
		glColor3f( 1.0f, 0.0f, 0.0f );
		glVertex2i( 0, 1 );
		glColor3f( 0.0f, 1.0f, 0.0f );
		glVertex2i( -1, -1 );
		glColor3f( 0.0f, 0.0f, 1.0f );
		glVertex2i( 1, -1 );
	}
	glEnd();
	glFlush();
}
