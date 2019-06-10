#include "Global.h"

#include "RendererD3D.h"

RendererD3D::RendererD3D() noexcept
	:
	mFeatureLevel( D3D_FEATURE_LEVEL_9_1 )
{}

BOOL RendererD3D::Initialize( HWND window, int width, int height )
{
	mHwnd = window;
	mOutputWidth = std::max( width, 1 );
	mOutputHeight = std::max( height, 1 );

	CreateDevice();
	CreateResources();

	return TRUE;
}

BOOL RendererD3D::CreateDevice()
{
	// Interface for D3D device and context.
	D3D_FEATURE_LEVEL levels[] = {
	D3D_FEATURE_LEVEL_9_1,
	D3D_FEATURE_LEVEL_9_2,
	D3D_FEATURE_LEVEL_9_3,
	D3D_FEATURE_LEVEL_10_0,
	D3D_FEATURE_LEVEL_10_1,
	D3D_FEATURE_LEVEL_11_0,
	D3D_FEATURE_LEVEL_11_1
	};

	// This flag adds support for surfaces with a color-channel ordering different
	// from the API default. It is required for compatibility with Direct2d.
	UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(DEBUG) || defined(_DEBUG)
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Create the Direct3D 11 API device object and a corresponding context.
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;

	if( FAILED( D3D11CreateDevice(
		nullptr,								// Specify nullptr to use the default adapter.
		D3D_DRIVER_TYPE_HARDWARE,				// Create a deice using the hardware graphics driver.
		0,										// Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
		deviceFlags,							// Set debug and Direct2d compatibility flags.
		levels,									// List of feature levels this APP can support.
		ARRAYSIZE( levels ),					// Size of the list above.
		D3D11_SDK_VERSION,						// Always set this to D3D11_SDK_VERSION for Windows Store Apps.
		device.ReleaseAndGetAddressOf(),		// Returns the Direct3D device created.
		&mFeatureLevel,							// Returns feature level of device created.
		context.ReleaseAndGetAddressOf() ) ) )	// Returns the device immediate context.)
	{
		REPORTMSG( D3D11CreateDevice(), FAILED, D3D11CreateDevice() failed to create device. );
		return FALSE;
	}

	// Store pointers to the Direct3D 11.1 API device and immediate context.
	if( FAILED( device.As( &mDevice ) ) )
	{
		REPORTMSG( device.As(), FAILED, device.As() failed to assign mDevice a ID3D11Device. );
		return FALSE;
	}

	if( FAILED( context.As( &mContext ) ) )
	{
		REPORTMSG( context.As(), FAILED, context.As() failed to assign mContext a ID3D11DeviceContext. );
		return FALSE;
	}

	return TRUE;
}

BOOL RendererD3D::CreateResources()
{
	// Clear the previous window size specific context.
	ID3D11RenderTargetView* nullViews[] = { nullptr };
	mContext->OMSetRenderTargets( _countof( nullViews ), nullViews, nullptr );
	mRenderTargetView.Reset();
	mDepthStencilView.Reset();
	mContext->Flush();

	UINT
		backBufferWidth = static_cast< UINT >( mOutputWidth ),
		backBufferHeight = static_cast< UINT >( mOutputHeight );
	DXGI_FORMAT
		backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM,
		depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	UINT backBufferCount = 2;

	// If the swap chain already exists, resize it, otherwise create one.
	if( mSwapChain )
	{
		HRESULT hr = mSwapChain->ResizeBuffers( backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0 );

		if( hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET )
		{
			// If the device was removed for any reason, a new device and swap chain will need to be created.
			OnDeviceLost();

			// Everything is set up now. Do not continue execution of this method. OnDeviceLost will re-enter this method
			// and correctly set up the new device.
			return TRUE;
		}
		else
		{
			if( FAILED( hr ) )
			{
				REPORTMSG( ResizeBuffers(), FAILED, ResizeBuffers() failed to resize mSwapChain buffers. );
				return FALSE;
			}
		}
	}
	else
	{
		// First, retrieve the underlying DXGI Device from the D3D Device.
		Microsoft::WRL::ComPtr<IDXGIDevice1> dxgiDevice;
		if( FAILED( mDevice.As( &dxgiDevice ) ) )
		{
			REPORTMSG( mDevice.As(), FAILED, mDevice.As() failed to retrieve IDXGIDevice1 from dxgiDevice. );
			return FALSE;
		}

		// Identify the physical adapter this device is running on.
		Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
		if( FAILED( dxgiDevice->GetAdapter( dxgiAdapter.GetAddressOf() ) ) )
		{
			REPORTMSG( GetAdapter(), FAILED, GetAdapter() failed to identify the physical adapter from dxgiDevice. );
			return FALSE;
		}

		// And obtain the factory object that created it.
		Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory;
		if( FAILED( dxgiAdapter->GetParent( IID_PPV_ARGS( dxgiFactory.GetAddressOf() ) ) ) )
		{
			REPORTMSG( GetParent(), FAILED, GetParent() failed to obtain the factory object that created it. );
			return FALSE;
		}

		// Create the descriptor for the swap chain.
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.Width = backBufferWidth;
		swapChainDesc.Height = backBufferHeight;
		swapChainDesc.Format = backBufferFormat;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = backBufferCount;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
		fsSwapChainDesc.Windowed = TRUE;

		// Create a SwapChain from a Win32 window.
		;
		if( FAILED( dxgiFactory->CreateSwapChainForHwnd(
			mDevice.Get(),
			mHwnd,
			&swapChainDesc,
			&fsSwapChainDesc,
			nullptr,
			mSwapChain.ReleaseAndGetAddressOf() ) ) )
		{
			REPORTMSG( CreateSwapChainForHwnd(), FAILED, CreateSwapChainForHwnd() failed to create a swap chain from a window. );
			return FALSE;
		}
	}
	// Obtain the back-buffer for this window which will be the final 3D render target.
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	if( FAILED( mSwapChain->GetBuffer( 0, IID_PPV_ARGS( backBuffer.GetAddressOf() ) ) ) )
	{
		REPORTMSG( GetBuffer(), FAILED, GetBuffer() failed to obtain the back-buffer for final render target. );
		return FALSE;
	}

	// Create a view interface on the render target to use on bind.
	if( FAILED( mDevice->CreateRenderTargetView( backBuffer.Get(), nullptr, mRenderTargetView.ReleaseAndGetAddressOf() ) ) )
	{
		REPORTMSG( CreateRenderTargetView(), FAILED, CreateRenderTargetView() failed to create a view interface on the render target. );
		return FALSE;
	}

	// Allocate a 2-D surface as the depth/stencil buffer and
	// create a DepthStencil view on this surface to use on bind.
	CD3D11_TEXTURE2D_DESC depthStencilDesc( depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL );

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencil;
	if( FAILED( mDevice->CreateTexture2D( &depthStencilDesc, nullptr, depthStencil.GetAddressOf() ) ) )
	{
		REPORTMSG( CreateTexture2D(), FAILED, CreateTexture2D() failed to allocate a 2-D surface ID3D11Texture2D. );
		return FALSE;
	}

	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc( D3D11_DSV_DIMENSION_TEXTURE2D );
	if( FAILED( mDevice->CreateDepthStencilView( depthStencil.Get(), &depthStencilViewDesc, mDepthStencilView.ReleaseAndGetAddressOf() ) ) )
	{
		REPORTMSG( CreateDepthStencilView(), FAILED, CreateDepthStencilView() failed to to create a depth stencil on the surface. );
		return FALSE;
	}

	return TRUE;
}

void RendererD3D::OnDeviceLost()
{
	mDepthStencilView.Reset();
	mRenderTargetView.Reset();
	mSwapChain.Reset();
	mContext.Reset();
	mDevice.Reset();

	CreateDevice();
	CreateResources();
}

void RendererD3D::Render()
{
	Clear();
	{
	}
	Present();
}

void RendererD3D::Terminate()
{
	if( mDepthStencilView ) mDepthStencilView->Release();
	if( mRenderTargetView ) mRenderTargetView->Release();
	if( mSwapChain ) mSwapChain->Release();
	if( mContext ) mContext->Release();
	if( mDevice ) mDevice->Release();
}

void RendererD3D::Clear()
{
	// Clear the views.
	mContext->ClearRenderTargetView( mRenderTargetView.Get(), DirectX::Colors::Coral );
	mContext->ClearDepthStencilView( mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0 );

	// Set the view-port.
	CD3D11_VIEWPORT viewport( 0.0f, 0.0f, static_cast< float >( mOutputWidth ), static_cast< float >( mOutputHeight ) );
	mContext->RSSetViewports( 1, &viewport );
}

void RendererD3D::Present()
{
	// The first argument instructs DXGI to block until VSYNC, putting the application
	// to sleep until the next VSYNC. This ensures we don't waste any cycles rendering
	// frames that will never be displayed to the screen.
	HRESULT hr = mSwapChain->Present( 1, 0 );

	// If the device was reset we must completely reinitialize the renderer.
	if( hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET )
	{
		OnDeviceLost();
	}
	else
	{
		if( FAILED( hr ) )
			REPORTMSG( Present(), FAILED, Present() failed to display mSwapChain. );
	}
}
