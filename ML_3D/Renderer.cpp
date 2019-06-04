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
	int
		pf,
		n;
	LOGPALETTE* lpPal;

	// Choose and set a best-match pixel format.
	ZeroMemory( &mPFD, sizeof( mPFD ) );
	mPFD.nSize = sizeof( PIXELFORMATDESCRIPTOR );
	mPFD.nVersion = 1;
	mPFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	mPFD.iPixelType = PFD_TYPE_RGBA;
	mPFD.cColorBits = 32;
	//mPFD.cDepthBits = 32;

	pf = ChoosePixelFormat( mHDC, &mPFD );

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

	if( mPFD.dwFlags & PFD_NEED_PALETTE ||
		mPFD.iPixelType == PFD_TYPE_COLORINDEX )
	{
		n = 1 << mPFD.cColorBits;
		if( n > 256 ) n = 256;

		lpPal = ( LOGPALETTE* )malloc( sizeof( LOGPALETTE ) * sizeof( PALETTEENTRY ) * n );
		ZeroMemory( lpPal, sizeof( LOGPALETTE ) + sizeof( PALETTEENTRY ) * n );
		lpPal->palVersion = 0x300;
		lpPal->palNumEntries = n;

		GetSystemPaletteEntries( mHDC, 0, n, &lpPal->palPalEntry[0] );

		/* If the pixel type is RGBA, then we want to make an RGB ramp,
		otherwise (color index) set individual colors. */

		if( mPFD.iPixelType == PFD_TYPE_RGBA )
		{
			int
				redMask = ( 1 << mPFD.cRedBits ) - 1,
				greenMask = ( 1 << mPFD.cGreenBits ) - 1,
				blueMask = ( 1 << mPFD.cBlueBits ) - 1;

			// Fill in the entries with an RGB color ramp.
			for( int i = 0; i < n; ++i )
			{
				lpPal->palPalEntry[i].peRed = ( ( ( i >> mPFD.cRedShift ) & redMask ) * 255 ) / redMask;
				lpPal->palPalEntry[i].peGreen = ( ( ( i >> mPFD.cGreenShift ) & greenMask ) * 255 ) / greenMask;
				lpPal->palPalEntry[i].peBlue = ( ( ( i >> mPFD.cBlueShift ) & blueMask ) * 255 ) / blueMask;
				lpPal->palPalEntry[i].peFlags = 0;
			}
		}
		else
		{
			lpPal->palPalEntry[0].peRed = 0;
			lpPal->palPalEntry[0].peGreen = 0;
			lpPal->palPalEntry[0].peBlue = 0;
			lpPal->palPalEntry[0].peFlags = PC_NOCOLLAPSE;
			lpPal->palPalEntry[1].peRed = 255;
			lpPal->palPalEntry[1].peGreen = 0;
			lpPal->palPalEntry[1].peBlue = 0;
			lpPal->palPalEntry[1].peFlags = PC_NOCOLLAPSE;
			lpPal->palPalEntry[2].peRed = 0;
			lpPal->palPalEntry[2].peGreen = 255;
			lpPal->palPalEntry[2].peBlue = 0;
			lpPal->palPalEntry[2].peFlags = PC_NOCOLLAPSE;
			lpPal->palPalEntry[3].peRed = 0;
			lpPal->palPalEntry[3].peGreen = 0;
			lpPal->palPalEntry[3].peBlue = 255;
			lpPal->palPalEntry[3].peFlags = PC_NOCOLLAPSE;
		}
		mHPALETTE = CreatePalette( lpPal );
		if( mHPALETTE )
		{
			SelectPalette( mHDC, mHPALETTE, FALSE );
			RealizePalette( mHDC );
		}

		free( lpPal );
	}

	mHRC = wglCreateContext( mHDC );
	wglMakeCurrent( mHDC, mHRC );
}

void Renderer::Render()
{
	Clear();
	glRotatef( 0.2f, 0.0f, 0.0f, 1.0f );
	glBegin( GL_TRIANGLES );
	glIndexi( 1 );
	glColor3f( 1.0f, 0.0f, 0.0f );
	glVertex2i( 0, 1 );
	glIndexi( 2 );
	glColor3f( 0.0f, 1.0f, 0.0f );
	glVertex2i( -1, -1 );
	glIndexi( 3 );
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
	SwapBuffers( mHDC );
}

void Renderer::Terminate()
{
	wglMakeCurrent( nullptr, nullptr );
	ReleaseDC( mHwnd, mHDC );
	wglDeleteContext( mHRC );

	if( mHPALETTE )
		DeleteObject( mHPALETTE );
}
