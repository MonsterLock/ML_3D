#include "Global.h"
#include "GraphicsD3D.h"

extern StepTimer stepTimer;

GraphicsD3D::GraphicsD3D() noexcept
	:
	mFeatureLevel( D3D_FEATURE_LEVEL_9_1 ),
	mDevice( nullptr ),
	mContext( nullptr ),
	mSwapChain( nullptr ),
	mRenderTargetView( nullptr ),
	mDepthStencilView( nullptr ),
	mDepthStencilBuffer( nullptr ),
	mRasterState( nullptr )
{}

void GraphicsD3D::Initialize( HWND window )
{
	RECT rc;
	GetClientRect( window, &rc );

	mHwnd = window;
	mOutputWidth = std::max( static_cast< int >( rc.right - rc.left ), 1 );
	mOutputHeight = std::max( static_cast< int >( rc.bottom - rc.top ), 1 );

	CreateDevice();
	CreateResources();
}

void GraphicsD3D::Render()
{
	Clear();

	// Render Code.

	Present();
}

void GraphicsD3D::Terminate()
{
	// TODO: Add D3D resource clean-up here.

	// Release application's D3D objects.
	mRasterState.Reset();
	mDepthStencilBuffer.Reset();
	mDepthStencilState.Reset();
	mDepthStencilView.Reset();
	mRenderTargetView.Reset();
	mSwapChain.Reset();
	mContext.Reset();
	mDevice.Reset();
}

ID3D11Device * GraphicsD3D::GetDevice()
{
	return mDevice.Get();
}

ID3D11DeviceContext * GraphicsD3D::GetContext()
{
	return mContext.Get();
}

void GraphicsD3D::GetWorldMatrix( XMMATRIX & worldMaxtix )
{
	worldMaxtix = mWorld;
}

void GraphicsD3D::GetProjectionMatrix( XMMATRIX & projMatrix )
{
	projMatrix = mProj;
}

void GraphicsD3D::GetOrthoMatrix( XMMATRIX & orthoMatrix )
{
	orthoMatrix = mOrtho;
}

void GraphicsD3D::GetGraphicsCardDesc()
{
	std::wstring graphicsCardDesc = L"Graphics Card: ";
	graphicsCardDesc += mVideoCardDescription;
	graphicsCardDesc += L"\nMemory: ";
	graphicsCardDesc += std::to_wstring( mVideoCardMemory );
	MessageBox( nullptr, graphicsCardDesc.c_str(), L"Info", MB_OK | MB_ICONINFORMATION );
}

void GraphicsD3D::Clear()
{
	// Clear the views.
	mContext->ClearRenderTargetView( mRenderTargetView.Get(), Colors::LightSteelBlue );
	mContext->ClearDepthStencilView( mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0 );

	//mContext->OMSetRenderTargets( 1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get() );
	// Set the view-port.
	//CD3D11_VIEWPORT viewport( 0.0f, 0.0f, static_cast< float >( mOutputWidth ), static_cast< float >( mOutputHeight ) );
	//mContext->RSSetViewports( 1, &viewport );
}

void GraphicsD3D::Present()
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
		TESTRESULT( FAILED( hr ) );
	}
}

// Device dependent resources.
void GraphicsD3D::CreateDevice()
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

	TESTRESULT( FAILED( D3D11CreateDevice(
		nullptr,								// Specify nullptr to use the default adapter.
		D3D_DRIVER_TYPE_HARDWARE,				// Create a deice using the hardware graphics driver.
		0,										// Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
		deviceFlags,							// Set debug and Direct2d compatibility flags.
		levels,									// List of feature levels this APP can support.
		ARRAYSIZE( levels ),					// Size of the list above.
		D3D11_SDK_VERSION,						// Always set this to D3D11_SDK_VERSION for Windows Store Apps.
		device.ReleaseAndGetAddressOf(),		// Returns the Direct3D device created.
		&mFeatureLevel,							// Returns feature level of device created.
		context.ReleaseAndGetAddressOf() ) ) );	// Returns the device immediate context.)

	// Store pointers to the Direct3D 11.1 API device and immediate context.
	TESTRESULT( FAILED( device.As( &mDevice ) ) );

	TESTRESULT( FAILED( context.As( &mContext ) ) );
}

// Allocate all memory resources that change on a window resize event.
void GraphicsD3D::CreateResources()
{
	// Clear the previous window size specific context.
	ID3D11RenderTargetView* nullViews[] = { nullptr };
	mContext->OMSetRenderTargets( _countof( nullViews ), nullViews, nullptr );
	mRenderTargetView.Reset();
	mDepthStencilView.Reset();
	mRasterState.Reset();
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

			/* Everything is set up now. Do not continue execution of this method.
			OnDeviceLost will re-enter this method and correctly set up the new device.*/
			return;
		}
		else
		{
			TESTRESULT( FAILED( hr ) );
		}
	}
	else
	{
		// First, retrieve the underlying DXGI Device from the D3D Device.
		Microsoft::WRL::ComPtr<IDXGIDevice1> dxgiDevice;
		TESTRESULT( FAILED( mDevice.As( &dxgiDevice ) ) );

		// Identify the physical adapter this device is running on.
		Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
		TESTRESULT( FAILED( dxgiDevice->GetAdapter( dxgiAdapter.GetAddressOf() ) ) );

		// And obtain the factory object that created it.
		Microsoft::WRL::ComPtr<IDXGIFactory> dxgiFactory;
		TESTRESULT( FAILED( dxgiAdapter->GetParent( IID_PPV_ARGS( dxgiFactory.GetAddressOf() ) ) ) );

		// Get the adapter (video card) description.
		DXGI_ADAPTER_DESC dxgiAdapterDesc;
		TESTRESULT( FAILED( dxgiAdapter->GetDesc( &dxgiAdapterDesc ) ) );
		mVideoCardDescription = dxgiAdapterDesc.Description;
		mVideoCardMemory = static_cast<int>( dxgiAdapterDesc.DedicatedVideoMemory / 1024 / 1024 );

		// Create a descriptor for the swap chain.
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = backBufferCount;
		swapChainDesc.BufferDesc.Width = mOutputWidth;
		swapChainDesc.BufferDesc.Height = mOutputHeight;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = mHwnd;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = 0;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
		fsSwapChainDesc.Windowed = TRUE;
		// Create a SwapChain from a Win32 window.
		TESTRESULT( FAILED( dxgiFactory->CreateSwapChain(
			mDevice.Get(),
			&swapChainDesc,
			mSwapChain.ReleaseAndGetAddressOf() ) ) );
		dxgiFactory->MakeWindowAssociation( mHwnd, DXGI_MWA_NO_ALT_ENTER );
	}
	// Obtain the back-buffer for this window which will be the final 3D render target.
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	TESTRESULT( FAILED( mSwapChain->GetBuffer( 0, IID_PPV_ARGS( backBuffer.GetAddressOf() ) ) ) );

	// Create a view interface on the render target to use on bind.
	TESTRESULT( FAILED( mDevice->CreateRenderTargetView( backBuffer.Get(), nullptr, mRenderTargetView.ReleaseAndGetAddressOf() ) ) );

	/* Allocate a 2-D surface as the depth/stencil buffer and
	create a DepthStencil view on this surface to use on bind.*/
	// Set up the description of the depth buffer.
	CD3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory( &depthBufferDesc, sizeof( depthBufferDesc ) );
	depthBufferDesc.Width = backBufferWidth;
	depthBufferDesc.Height = backBufferHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = depthBufferFormat;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Create the texture for the depth buffer using the filled out description.
	TESTRESULT( FAILED( mDevice->CreateTexture2D( &depthBufferDesc, nullptr, mDepthStencilBuffer.GetAddressOf() ) ) );

	// Set up the depth stencil state.
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory( &depthStencilDesc, sizeof( depthStencilDesc ) );
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	TESTRESULT( FAILED( mDevice->CreateDepthStencilState( &depthStencilDesc, &mDepthStencilState ) ) );

	// Set the depth stencil state.
	mContext->OMSetDepthStencilState( mDepthStencilState.Get(), 1 );

	// Set up the depth stencil view.
	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory( &depthStencilViewDesc, sizeof( depthStencilViewDesc ) );
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	TESTRESULT( FAILED( mDevice->CreateDepthStencilView( mDepthStencilBuffer.Get(), &depthStencilViewDesc, mDepthStencilView.ReleaseAndGetAddressOf() ) ) );

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	mContext->OMSetRenderTargets( 1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get() );

	// Setup the raster description which will determine how and what polygons will be drawn.
	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;
	TESTRESULT( FAILED( mDevice->CreateRasterizerState( &rasterDesc, &mRasterState ) ) );
	// Now set the rasterizer state.
	mContext->RSSetState( mRasterState.Get() );

	D3D11_VIEWPORT viewport;
	// Setup the viewport for rendering.
	viewport.Width = static_cast< float >( mOutputWidth );
	viewport.Height = static_cast< float >( mOutputHeight );
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	mContext->RSSetViewports( 1, &viewport );

	/* Setup the projection matrix to keep a copy of this
	matrix so that we can pass it to our shaders that will
	be used to render our scenes.*/
	float
		fieldOfView = static_cast< float >( XM_PI ) / 4.0f,
		screenAspect = static_cast< float >( mOutputWidth ) / static_cast< float >( mOutputHeight );
	mProj = XMMatrixPerspectiveFovLH( fieldOfView, screenAspect, mScreenNear, mScreenDepth );

	/* Initialize the world matrix to the identity matrix and
	keep a copy of it in this object. The copy will be needed
	to be passed to the shaders for rendering*/
	mWorld = XMMatrixIdentity();

	// Initialize an orthographic projection matrix.
	mOrtho = XMMatrixOrthographicLH( static_cast< float >( mOutputWidth ), static_cast< float >( mOutputHeight ), mScreenNear, mScreenDepth );
}

void GraphicsD3D::OnDeviceLost()
{
	Terminate();
	CreateDevice();
	CreateResources();
}
