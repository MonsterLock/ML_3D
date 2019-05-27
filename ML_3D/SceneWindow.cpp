#include "SceneWindow.h"
#include "windowsx.h"
#include <Commctrl.h>
#include <string>

template <class T> void SafeRelease( T **ppT )
{
	if( *ppT )
	{
		( *ppT )->Release();
		*ppT = NULL;
	}
}

void SceneWindow::CalculateLayout()
{
	if( pRenderTarget )
	{
		D2D1_SIZE_F size = pRenderTarget->GetSize();
		const float
			x = size.width / 2,
			y = size.height / 2,
			radius = min( x, y );
		ellipse = D2D1::Ellipse( D2D1::Point2F( x, y ), radius, radius );
	}
}

HRESULT SceneWindow::CreateGraphicsResources()
{
	HRESULT hr = S_OK;

	if( !pRenderTarget )
	{
		RECT rc;
		GetClientRect( Wnd(), &rc );

		D2D1_SIZE_U size = D2D1::SizeU( rc.right, rc.bottom );

		hr = pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties( Wnd(), size ),
			&pRenderTarget );

		if( SUCCEEDED( hr ) )
		{
			const D2D1_COLOR_F color = D2D1::ColorF( 1.0f, 1.0f, 0.0f );
			hr = pRenderTarget->CreateSolidColorBrush( color, &pBrush );

			if( SUCCEEDED( hr ) )
			{
				CalculateLayout();
			}
		}
	}
	return hr;
}

void SceneWindow::DiscardGraphicsResources()
{
	if( pRenderTarget )
	{
		pRenderTarget->Release();
		pRenderTarget = nullptr;
	}
	if( pBrush )
	{
		pBrush->Release();
		pBrush = nullptr;
	}
}

void SceneWindow::OnPaint()
{
	HRESULT hr = CreateGraphicsResources();

	if( SUCCEEDED( hr ) )
	{
		PAINTSTRUCT ps;
		BeginPaint( Wnd(), &ps );

		pRenderTarget->BeginDraw();

		pRenderTarget->Clear( D2D1::ColorF( D2D1::ColorF::HotPink ) );
		pRenderTarget->FillEllipse( ellipse, pBrush );

		hr = pRenderTarget->EndDraw();

		if( FAILED( hr ) || hr == D2DERR_RECREATE_TARGET )
		{
			DiscardGraphicsResources();
		}

		EndPaint( Wnd(), &ps );
	}
}

void SceneWindow::Resize()
{
	if( pRenderTarget )
	{
		RECT rc;
		GetClientRect( Wnd(), &rc );

		D2D1_SIZE_U size = D2D1::SizeU( rc.right, rc.bottom );

		pRenderTarget->Resize( size );
		CalculateLayout();
		InvalidateRect( Wnd(), nullptr, FALSE );
	}
}

LRESULT SceneWindow::HandleSubWndMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_CREATE:
			{
				if( FAILED( D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory ) ) )
				{
					return -1;
				}
				return 0;
			}
			break;
		case WM_PAINT:
			{
				OnPaint();
			}
			break;
		case WM_SIZE:
			{
				Resize();
			}
			break;
		case WM_DESTROY:
			{
				DiscardGraphicsResources();

				if( pFactory )
				{
					pFactory->Release();
					pFactory = nullptr;
				}

				PostQuitMessage( 0 );
			}
			break;
		default:
			{
				return DefMDIChildProc( Wnd(), uMsg, wParam, lParam );
			}
	}

	return 0;
}
