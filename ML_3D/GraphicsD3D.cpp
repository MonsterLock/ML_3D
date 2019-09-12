#include "Global.h"
#include "GraphicsD3D.h"

GraphicsD3D::GraphicsD3D( ) noexcept
	:
	mFeatureLevel( D3D_FEATURE_LEVEL_11_1 ),
	mDevice( nullptr ),
	mContext( nullptr ),
	mSwapChain( nullptr ),
	mRenderTargetView( nullptr ),
	mDepthStencilState( nullptr ),
	mDepthStencilStateDisabled( nullptr ),
	mDepthStencilView( nullptr ),
	mDepthStencilBuffer( nullptr ),
	mRasterStates( nullptr ),
	mBlendStates( nullptr )
{ }

bool GraphicsD3D::Initialize( HWND window, UINT width, UINT height )
{
	mHwnd = window;
	mWidth = width;
	mHeight = height;

	if( ISERROR2( !CreateDevice( ), Failed to create device. ) )
		return false;

	if( ISERROR2( !CreateResources( ), Failed to create resources. ) )
		return false;

	return true;
}

void GraphicsD3D::BeginUpdate( XMVECTORF32 color )
{
	mContext->ClearRenderTargetView( mRenderTargetView.Get( ), color );
	mContext->ClearDepthStencilView( mDepthStencilView.Get( ), D3D11_CLEAR_DEPTH, 1.0f, 0 );
}

void GraphicsD3D::EndUpdate( )
{
	HRESULT hr = mSwapChain->Present( 1, 0 );

	if( hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET )
		OnDeviceLost( );
	else
		ISERROR1( FAILED( hr ) );
}

void GraphicsD3D::Shutdown( )
{
	mSwapChain->SetFullscreenState( false, nullptr );

	ShutdownBlendStates( );
	ShutdownRasterStates( );

	mDepthStencilStateDisabled.Reset( );
	mDepthStencilState.Reset( );
	mDepthStencilBuffer.Reset( );
	mDepthStencilView.Reset( );
	mRenderTargetView.Reset( );
	mSwapChain.Reset( );
	mContext.Reset( );
	mDevice.Reset( );
}

bool GraphicsD3D::CreateDevice( )
{
	D3D_FEATURE_LEVEL levels[] = {
	D3D_FEATURE_LEVEL_11_1,
	D3D_FEATURE_LEVEL_11_0,
	D3D_FEATURE_LEVEL_10_1,
	D3D_FEATURE_LEVEL_10_0,
	};

	UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	#if defined(DEBUG) || defined(_DEBUG)
	flags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;

	if( ISERROR1( FAILED( D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		flags,
		levels,
		ARRAYSIZE( levels ),
		D3D11_SDK_VERSION,
		device.ReleaseAndGetAddressOf( ),
		&mFeatureLevel,
		context.ReleaseAndGetAddressOf( ) ) ) ) )
		return false;

	if( ISERROR1( FAILED( device.As( &mDevice ) ) ) )
		return false;

	if( ISERROR1( FAILED( context.As( &mContext ) ) ) )
		return false;

	// Device independent objects

	return true;
}

bool GraphicsD3D::CreateResources( )
{
	ID3D11RenderTargetView* nullViews[] = { nullptr };
	mContext->OMSetRenderTargets( _countof( nullViews ), nullViews, nullptr );
	mRenderTargetView.Reset( );
	mDepthStencilView.Reset( );
	mContext->Flush( );

	UINT backBufferWidth = static_cast< UINT >( mWidth ),
		backBufferHeight = static_cast< UINT >( mHeight ),
		backBufferCount = 2;

	//-------------------------------------------------------------------------------------------------------------------------------------------- SWAP CHAIN
	if( mSwapChain )
	{
		HRESULT hr = mSwapChain->ResizeBuffers( backBufferCount, backBufferWidth, backBufferHeight, DXGI_FORMAT_B8G8R8A8_UNORM, 0 );

		if( hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET )
		{
			OnDeviceLost( );

			return true;
		}
		else
			ISERROR1( FAILED( hr ) );
	}
	else
	{
		Microsoft::WRL::ComPtr<IDXGIDevice1> dxgiDevice;
		ISERROR1( FAILED( mDevice.As( &dxgiDevice ) ) );

		Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
		ISERROR1( FAILED( dxgiDevice->GetAdapter( dxgiAdapter.GetAddressOf( ) ) ) );

		Microsoft::WRL::ComPtr<IDXGIFactory> dxgiFactory;
		ISERROR1( FAILED( dxgiAdapter->GetParent( IID_PPV_ARGS( dxgiFactory.GetAddressOf( ) ) ) ) );

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		ZeroMemory( &swapChainDesc, sizeof( swapChainDesc ) );
		swapChainDesc.BufferDesc.Width = mWidth;
		swapChainDesc.BufferDesc.Height = mHeight;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = backBufferCount;
		swapChainDesc.OutputWindow = mHwnd;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
		fsSwapChainDesc.Windowed = FALSE;

		ISERROR1( FAILED( dxgiFactory->CreateSwapChain(
			mDevice.Get( ),
			&swapChainDesc,
			mSwapChain.ReleaseAndGetAddressOf( ) ) ) );
	}

	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	if( ISERROR1( FAILED( mSwapChain->GetBuffer( 0, IID_PPV_ARGS( backBuffer.GetAddressOf( ) ) ) ) ) )
		return false;

	if( ISERROR1( FAILED( mDevice->CreateRenderTargetView( backBuffer.Get( ), nullptr, mRenderTargetView.GetAddressOf( ) ) ) ) )
		return false;

	//-------------------------------------------------------------------------------------------------------------------------------------------- DEPTH BUFFER
	CreateDepthBuffer( mDepthStencilBuffer.GetAddressOf( ), mWidth, mHeight );

	//-------------------------------------------------------------------------------------------------------------------------------------------- DEPTH STENCIL
	CreateDepthStencil( mDepthStencilState.GetAddressOf( ), true );

	mContext->OMSetDepthStencilState( mDepthStencilState.Get( ), 1 );

	CreateDepthStencil( mDepthStencilStateDisabled.GetAddressOf( ), false );

	//-------------------------------------------------------------------------------------------------------------------------------------------- DEPTH STENCIL VIEW
	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory( &depthStencilViewDesc, sizeof( depthStencilViewDesc ) );
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	if( ISERROR1( FAILED( mDevice->CreateDepthStencilView( mDepthStencilBuffer.Get( ), &depthStencilViewDesc, mDepthStencilView.GetAddressOf( ) ) ) ) )
		return false;

	SetRenderTarget( );

	//-------------------------------------------------------------------------------------------------------------------------------------------- RASTER
	mRasterStates = new Microsoft::WRL::ComPtr<ID3D11RasterizerState>[raster_num];
	CreateResterizeState( mRasterStates[raster_default].GetAddressOf( ), D3D11_FILL_SOLID, D3D11_CULL_BACK );

	mContext->RSSetState( mRasterStates[raster_default].Get( ) );

	CreateResterizeState( mRasterStates[raster_wiremode].GetAddressOf( ), D3D11_FILL_WIREFRAME, D3D11_CULL_BACK );

	//-------------------------------------------------------------------------------------------------------------------------------------------- BLEND
	mBlendStates = new Microsoft::WRL::ComPtr<ID3D11BlendState>[blend_num];
	CreateBlendState( mBlendStates[blend_default].GetAddressOf( ), false, D3D11_BLEND_ONE, D3D11_BLEND_INV_SRC_ALPHA );
	CreateBlendState( mBlendStates[blend_simple].GetAddressOf( ), true, D3D11_BLEND_ONE, D3D11_BLEND_INV_SRC_ALPHA );
	CreateBlendState( mBlendStates[blend_texture].GetAddressOf( ), true, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA );
	CreateBlendState( mBlendStates[blend_particle].GetAddressOf( ), true, D3D11_BLEND_ONE, D3D11_BLEND_ONE );

	//-------------------------------------------------------------------------------------------------------------------------------------------- VIEW PORT
	D3D11_VIEWPORT viewport;
	ZeroMemory( &viewport, sizeof( viewport ) );
	viewport.Width = static_cast< float >( mWidth );
	viewport.Height = static_cast< float >( mHeight );
	viewport.MaxDepth = 1.0f;
	mContext->RSSetViewports( 1, &viewport );

	return true;
}

void GraphicsD3D::OnDeviceLost( )
{
	Shutdown( );
	CreateDevice( );
	CreateResources( );
}

bool GraphicsD3D::CreateDepthBuffer( ID3D11Texture2D** buffer, UINT width, UINT height )
{
	CD3D11_TEXTURE2D_DESC depthBD;
	ZeroMemory( &depthBD, sizeof( depthBD ) );
	depthBD.Width = width;
	depthBD.Height = height;
	depthBD.MipLevels = 1;
	depthBD.ArraySize = 1;
	depthBD.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBD.SampleDesc.Count = 1;
	depthBD.Usage = D3D11_USAGE_DEFAULT;
	depthBD.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	if( ISERROR1( FAILED( mDevice->CreateTexture2D( &depthBD, nullptr, buffer ) ) ) )
		return false;

	return true;
}

bool GraphicsD3D::CreateDepthStencil( ID3D11DepthStencilState** depthStencilState, bool isDepthEnabled )
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory( &depthStencilDesc, sizeof( depthStencilDesc ) );
	depthStencilDesc.DepthEnable = isDepthEnabled;
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
	if( ISERROR1( FAILED( mDevice->CreateDepthStencilState( &depthStencilDesc, depthStencilState ) ) ) )
		return false;

	return true;
}

bool GraphicsD3D::CreateResterizeState( ID3D11RasterizerState **rasterizerState, D3D11_FILL_MODE  fillMode, D3D11_CULL_MODE  cullMode )
{
	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory( &rasterDesc, sizeof( rasterDesc ) );
	rasterDesc.FillMode = fillMode;
	rasterDesc.CullMode = cullMode;
	rasterDesc.DepthClipEnable = true;

	if( ISERROR1( FAILED( mDevice->CreateRasterizerState( &rasterDesc, rasterizerState ) ) ) )
		return false;

	return true;
}

bool GraphicsD3D::CreateBlendState( ID3D11BlendState **blendState, bool blendEnable, D3D11_BLEND srcBlend, D3D11_BLEND destBlend )
{
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory( &blendDesc, sizeof( blendDesc ) );
	blendDesc.RenderTarget[0].BlendEnable = blendEnable;
	blendDesc.RenderTarget[0].SrcBlend = srcBlend;
	blendDesc.RenderTarget[0].DestBlend = destBlend;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;
	if( ISERROR1( FAILED( mDevice->CreateBlendState( &blendDesc, blendState ) ) ) )
		return false;

	return true;
}

void GraphicsD3D::ShutdownRasterStates( )
{
	if( mRasterStates )
	{
		for( UINT i = 0; i < raster_num; i++ )
			mRasterStates[i].Reset( );

		delete[] mRasterStates;
		mRasterStates = nullptr;
	}
}

void GraphicsD3D::ShutdownBlendStates( )
{
	if( mBlendStates )
	{
		for( UINT i = 0; i < blend_num; i++ )
			mBlendStates[i].Reset( );

		delete[] mBlendStates;
		mBlendStates = nullptr;
	}
}

ID3D11Device * GraphicsD3D::GetDevice( )
{
	return mDevice.Get( );
}

ID3D11DeviceContext * GraphicsD3D::GetContext( )
{
	return mContext.Get( );
}

ID3D11DepthStencilView * GraphicsD3D::GetDepthStencilView( )
{
	return mDepthStencilView.Get( );
}

void GraphicsD3D::EnableZ( )
{
	mContext->OMSetDepthStencilState( mDepthStencilState.Get( ), 1 );
}

void GraphicsD3D::DisableZ( )
{
	mContext->OMSetDepthStencilState( mDepthStencilStateDisabled.Get( ), 1 );
}

void GraphicsD3D::SetRasterState( UINT state )
{
	switch( state )
	{
		case raster_default:
		{
			mContext->RSSetState( mRasterStates[raster_default].Get( ) );
		}
		break;
		case raster_wiremode:
		{
			mContext->RSSetState( mRasterStates[raster_wiremode].Get( ) );
		}
		break;
		default:
			break;
	}
}

void GraphicsD3D::SetBlendState( UINT state )
{
	switch( state )
	{
		case blend_default:
		{
			float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			mContext->OMSetBlendState( mBlendStates[blend_default].Get( ), blendFactor, 0xFFFFFFFF );
		}
		break;
		case GraphicsD3D::blend_simple:
		{
			float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			mContext->OMSetBlendState( mBlendStates[blend_simple].Get( ), blendFactor, 0xFFFFFFFF );
		}
		break;
		case GraphicsD3D::blend_texture:
		{
			float blendFactor[4] = { 0.75f, 0.75f, 0.75f, 1.0f };
			mContext->OMSetBlendState( mBlendStates[blend_texture].Get( ), blendFactor, 0xFFFFFFFF );
		}
		break;
		case GraphicsD3D::blend_particle:
		{
			float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			mContext->OMSetBlendState( mBlendStates[blend_particle].Get( ), blendFactor, 0xFFFFFFFF );
		}
		break;
		default:
			break;
	}
}

void GraphicsD3D::SetRenderTarget( )
{
	mContext->OMSetRenderTargets( 1, mRenderTargetView.GetAddressOf( ), mDepthStencilView.Get( ) );
}

template<typename T>
bool GraphicsD3D::SaveMesh( D3D11_PRIMITIVE_TOPOLOGY topology, UINT bufferIndex, T* vertIn, UINT vertexBytes, UINT* indices, UINT indexBytes )
{
	mModels[bufferIndex].stride = sizeof( T );

	mModels[bufferIndex].topology = topology;

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory( &bufferDesc, sizeof( bufferDesc ) );

	D3D11_SUBRESOURCE_DATA initData = {};
	ZeroMemory( &initData, sizeof( initData ) );

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = vertexBytes;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	initData.pSysMem = vertices;
	if( ISERROR1( FAILED( device->CreateBuffer( &bufferDesc, &initData, mModels[bufferIndex].vertices.GetAddressOf( ) ) ) ) ) return false;

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = indexCount;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	initData.pSysMem = indexBytes;
	if( ISERROR1( FAILED( device->CreateBuffer( &bufferDesc, &initData, mModels[bufferIndex].indices.GetAddressOf( ) ) ) ) ) return false;

	return true;
}

void GraphicsD3D::LoadMesh( UINT bufferIndex )
{
	UINT stride = mModels[bufferIndex].stride, offset = 0;

	mContext->IASetPrimitiveTopology( mModels[bufferIndex].topology );

	mContext->IASetVertexBuffers( 0, 1, mModels[bufferIndex].vertices.GetAddressOf( ), &stride, &offset );
	mContext->IASetIndexBuffer( mModels[bufferIndex].indices.Get( ), DXGI_FORMAT_R32_UINT, 0 );
}

bool GraphicsD3D::CreateBuffer( D3D11_USAGE usage, UINT byteWidth, ID3D11Buffer **buffer )
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof( bd ) );
	bd.Usage = usage;
	bd.ByteWidth = byteWidth;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	if( ISERROR1( FAILED( mDevice->CreateBuffer( &bd, nullptr, buffer ) ) ) )
		return false;

	return true;
}
