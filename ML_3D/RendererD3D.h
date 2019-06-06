#pragma once
//#include "Global.h"
#include "Renderer.h"

class RendererD3D : public Renderer
{
	D3D_FEATURE_LEVEL									mFeatureLevel;
	Microsoft::WRL::ComPtr<ID3D11Device1>				mDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1>		mContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain1>				mSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		mRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		mDepthStencilView;

	BOOL CreateDevice();
	BOOL CreateResources();
	void OnDeviceLost();

	void Clear();
	void Present();

public:
	RendererD3D() noexcept;

	// Initialization and management.
	BOOL Inititalize( HWND window, int width, int height );
	void Render();
	void Terminate();
};

