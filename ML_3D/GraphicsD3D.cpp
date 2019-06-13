#include "Global.h"
#include "GraphicsD3D.h"

extern StepTimer stepTimer;

GraphicsD3D::GraphicsD3D() noexcept : mFeatureLevel( D3D_FEATURE_LEVEL_9_1 ){}

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
	float cosTime = cosf( static_cast< float >( stepTimer.GetTotalSeconds() ) );
	m_world = DirectX::SimpleMath::Matrix::CreateRotationX( cosTime );
	m_world *= DirectX::SimpleMath::Matrix::CreateRotationY( cosTime* 1.5f );
	m_world *= DirectX::SimpleMath::Matrix::CreateRotationZ( cosTime * 2.0f );

	Clear();

	// Render Code.

	mContext->OMSetBlendState( m_states->Opaque(), nullptr, 0xFFFFFFFF );
	mContext->OMSetDepthStencilState( m_states->DepthNone(), 0 );
	mContext->RSSetState( m_raster.Get() );

	m_effect->SetWorld( m_world );
	m_effect2->SetWorld( m_world );

	m_effect->Apply( mContext.Get() );

	mContext->IASetInputLayout( m_inputLayout.Get() );

	m_batch->Begin();

	DirectX::VertexPositionColor v1( DirectX::SimpleMath::Vector3( 0.f, 1.0f, 0.5f ), DirectX::Colors::Cyan );
	DirectX::VertexPositionColor v2( DirectX::SimpleMath::Vector3( 2.0f, 0.0f, 0.5f ), DirectX::Colors::Fuchsia );
	DirectX::VertexPositionColor v3( DirectX::SimpleMath::Vector3( -2.0f, 0.0f, 0.5f ), DirectX::Colors::Coral );

	m_batch->DrawTriangle( v1, v2, v3 );

	DirectX::SimpleMath::Vector3 xaxis( 2.f, 0.f, 0.f );
	DirectX::SimpleMath::Vector3 yaxis( 0.f, 0.f, 2.f );
	DirectX::SimpleMath::Vector3 origin = DirectX::SimpleMath::Vector3::Zero;

	size_t divisions = 20;

	for( size_t i = 0; i <= divisions; i++ )
	{
		float fPercent = float( i ) / float( divisions );
		fPercent = ( fPercent * 2.0f ) - 1.0f;

		DirectX::SimpleMath::Vector3 scale = yaxis * fPercent + origin;

		DirectX::VertexPositionColor v1( scale - xaxis, DirectX::Colors::Gainsboro );
		DirectX::VertexPositionColor v2( scale + xaxis, DirectX::Colors::Gainsboro );
		m_batch->DrawLine( v1, v2 );
	}

	for( size_t i = 0; i <= divisions; ++i )
	{
		float fPercent = float( i ) / float( divisions );
		fPercent = ( fPercent * 2.0f ) - 1.0f;

		DirectX::SimpleMath::Vector3 scale = xaxis * fPercent + origin;

		DirectX::VertexPositionColor v1( scale - yaxis, DirectX::Colors::BlanchedAlmond );
		DirectX::VertexPositionColor v2( scale + yaxis, DirectX::Colors::BlanchedAlmond );
		m_batch->DrawLine( v1, v2 );
	}

	m_batch->End();

	m_shape->Draw( m_effect2.get(), m_inputLayout2.Get() );

	Present();
}

void GraphicsD3D::Terminate()
{
	// TODO: Add D3D resource clean-up here.
	m_texture.Reset();
	m_shape.reset();
	m_raster.Reset();
	m_states.reset();
	m_effect.reset();
	m_effect2.reset();
	m_batch.reset();
	m_inputLayout.Reset();
	m_inputLayout2.Reset();

	// Release application's D3D objects.
	mDepthStencilView.Reset();
	mRenderTargetView.Reset();
	mSwapChain.Reset();
	mContext.Reset();
	mDevice.Reset();
}

void GraphicsD3D::Clear()
{
	// Clear the views.
	mContext->ClearRenderTargetView( mRenderTargetView.Get(), DirectX::Colors::LightSteelBlue );
	mContext->ClearDepthStencilView( mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0 );

	mContext->OMSetRenderTargets( 1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get() );

	// Set the view-port.
	CD3D11_VIEWPORT viewport( 0.0f, 0.0f, static_cast< float >( mOutputWidth ), static_cast< float >( mOutputHeight ) );
	mContext->RSSetViewports( 1, &viewport );
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

	// TODO: Initialize device independent objects here (independent of window size).
	m_states = std::make_unique<DirectX::CommonStates>( mDevice.Get() );

	m_effect = std::make_unique<DirectX::BasicEffect>( mDevice.Get() );
	m_effect->SetVertexColorEnabled( true );

	void const* shaderByteCode;
	size_t byteCodeLength;

	m_effect->GetVertexShaderBytecode( &shaderByteCode, &byteCodeLength );

	TESTRESULT( FAILED( mDevice->CreateInputLayout(
		DirectX::VertexPositionColor::InputElements,
		DirectX::VertexPositionColor::InputElementCount,
		shaderByteCode,
		byteCodeLength,
		m_inputLayout.ReleaseAndGetAddressOf() ) ) );

	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>( mContext.Get() );

	CD3D11_RASTERIZER_DESC rastDesc( D3D11_FILL_SOLID, D3D11_CULL_NONE, FALSE,
									 D3D11_DEFAULT_DEPTH_BIAS, D3D11_DEFAULT_DEPTH_BIAS_CLAMP,
									 D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS, TRUE, FALSE, TRUE, FALSE );

	TESTRESULT( FAILED( mDevice->CreateRasterizerState( &rastDesc,
														m_raster.ReleaseAndGetAddressOf() ) ) );

	m_effect2 = std::make_unique<DirectX::BasicEffect>( mDevice.Get() );
	m_effect2->SetTextureEnabled( true );
	m_effect2->SetPerPixelLighting( true );
	m_effect2->SetLightingEnabled( true );
	m_effect2->SetLightEnabled( 0, true );
	m_effect2->SetLightDiffuseColor( 0, DirectX::Colors::White );
	m_effect2->SetLightDirection( 0, -DirectX::SimpleMath::Vector3::UnitZ );

	m_shape = DirectX::GeometricPrimitive::CreateGeoSphere( mContext.Get() );
	m_shape->CreateInputLayout( m_effect2.get(),
								m_inputLayout2.ReleaseAndGetAddressOf() );

	TESTRESULT(
		FAILED( DirectX::CreateWICTextureFromFile(
			mDevice.Get(),
			L"C:..\\earth.bmp",
			nullptr,
			m_texture.ReleaseAndGetAddressOf() ) ) );

	m_effect2->SetTexture( m_texture.Get() );

	m_world = DirectX::SimpleMath::Matrix::Identity;
}

// Allocate all memory resources that change on a window resize event.
void GraphicsD3D::CreateResources()
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
		Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory;
		TESTRESULT( FAILED( dxgiAdapter->GetParent( IID_PPV_ARGS( dxgiFactory.GetAddressOf() ) ) ) );

		// Create a descriptor for the swap chain.
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.Width = backBufferWidth;
		swapChainDesc.Height = backBufferHeight;
		swapChainDesc.Format = backBufferFormat;
		swapChainDesc.SampleDesc.Count = 4;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = backBufferCount;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
		fsSwapChainDesc.Windowed = TRUE;

		// Create a SwapChain from a Win32 window.
		TESTRESULT( FAILED( dxgiFactory->CreateSwapChainForHwnd(
			mDevice.Get(),
			mHwnd,
			&swapChainDesc,
			&fsSwapChainDesc,
			nullptr,
			mSwapChain.ReleaseAndGetAddressOf() ) ) );
		dxgiFactory->MakeWindowAssociation( mHwnd, DXGI_MWA_NO_ALT_ENTER );
	}
	// Obtain the back-buffer for this window which will be the final 3D render target.
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	TESTRESULT( FAILED( mSwapChain->GetBuffer( 0, IID_PPV_ARGS( backBuffer.GetAddressOf() ) ) ) );

	// Create a view interface on the render target to use on bind.
	TESTRESULT( FAILED( mDevice->CreateRenderTargetView( backBuffer.Get(), nullptr, mRenderTargetView.ReleaseAndGetAddressOf() ) ) );

	// Allocate a 2-D surface as the depth/stencil buffer and
	// create a DepthStencil view on this surface to use on bind.
	CD3D11_TEXTURE2D_DESC depthStencilDesc( depthBufferFormat,
											backBufferWidth, backBufferHeight,
											1, 1, D3D11_BIND_DEPTH_STENCIL, D3D11_USAGE_DEFAULT, 0, 4, 0 );

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencil;
	TESTRESULT( FAILED( mDevice->CreateTexture2D( &depthStencilDesc, nullptr, depthStencil.GetAddressOf() ) ) );

	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc( D3D11_DSV_DIMENSION_TEXTURE2DMS );
	TESTRESULT( FAILED( mDevice->CreateDepthStencilView( depthStencil.Get(), &depthStencilViewDesc, mDepthStencilView.ReleaseAndGetAddressOf() ) ) );

	// TODO: Initialize windows-size dependent objects here.
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(
		DirectX::SimpleMath::Vector3( 3.f, 3.f, 3.f ),
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::UnitY );

	m_proj = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		DirectX::XM_PI / 3.f,
		float( backBufferWidth ) / float( backBufferHeight ),
		0.1f,
		10.f );

	m_effect->SetView( m_view );
	m_effect->SetProjection( m_proj );

	m_effect2->SetView( m_view );
	m_effect2->SetProjection( m_proj );
}

void GraphicsD3D::OnDeviceLost()
{
	// TODO: Add D3D resource clean-up here.
	m_texture.Reset();
	m_shape.reset();
	m_raster.Reset();
	m_states.reset();
	m_effect.reset();
	m_effect2.reset();
	m_batch.reset();
	m_inputLayout.Reset();
	m_inputLayout2.Reset();

	// Release application's D3D objects.
	mDepthStencilView.Reset();
	mRenderTargetView.Reset();
	mSwapChain.Reset();
	mContext.Reset();
	mDevice.Reset();

	CreateDevice();
	CreateResources();
}
