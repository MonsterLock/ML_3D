#pragma once
#include "GraphicsAPI.h"

class GraphicsD3D : public GraphicsAPI
{
protected:
	// Fields
	D3D_FEATURE_LEVEL									mFeatureLevel;
	Microsoft::WRL::ComPtr<ID3D11Device>				mDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			mContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain>				mSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		mRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		mDepthStencilView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>		mDepthStencilState;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				mDepthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>		mRasterState;

	XMMATRIX
		mWorld,
		mProj,
		mOrtho;

	std::wstring mVideoCardDescription;
	int mVideoCardMemory;

	void Clear();

	void Present();

	void CreateDevice();
	void CreateResources();
	void OnDeviceLost();

public:
	GraphicsD3D() noexcept;

	// Initialization and management.
	void Initialize( HWND );
	void Render();
	void Terminate();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();

	void GetWorldMatrix( XMMATRIX& );
	void GetProjectionMatrix( XMMATRIX& );
	void GetOrthoMatrix( XMMATRIX& );

	void GetGraphicsCardDesc();
};

