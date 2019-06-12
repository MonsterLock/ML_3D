#pragma once
#include "Renderer.h"
#include "Effects.h"
#include "PrimitiveBatch.h"
#include "CommonStates.h"
#include "VertexTypes.h"
#include "SimpleMath.h"

class RendererD3D : public Renderer
{
protected:
	// Fields
	D3D_FEATURE_LEVEL									mFeatureLevel;
	Microsoft::WRL::ComPtr<ID3D11Device1>				mDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1>		mContext;

	Microsoft::WRL::ComPtr<IDXGISwapChain1>				mSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		mRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		mDepthStencilView;

	void Clear();
	void Present();

	BOOL CreateDevice();
	BOOL CreateResources();
	void OnDeviceLost();

	// TODO: Additional Fields.
	std::unique_ptr<DirectX::CommonStates> m_states;
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

public:
	RendererD3D() noexcept;

	// Initialization and management.
	void Initialize( HWND );
	void Render();
	void Terminate();
};

