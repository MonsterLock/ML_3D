#pragma once
#include "GraphicsAPI.h"
#include "Effects.h"
#include "GeometricPrimitive.h"
#include "PrimitiveBatch.h"
#include "CommonStates.h"
#include "VertexTypes.h"
#include "SimpleMath.h"
#include <WICTextureLoader.h>

class GraphicsD3D : public GraphicsAPI
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

	void CreateDevice();
	void CreateResources();
	void OnDeviceLost();

	// TODO: Additional Fields.
	std::unique_ptr<DirectX::CommonStates> m_states;
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	std::unique_ptr<DirectX::BasicEffect> m_effect2;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout2;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_raster;
	std::unique_ptr<DirectX::GeometricPrimitive> m_shape;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

public:
	GraphicsD3D() noexcept;

	// Initialization and management.
	void Initialize( HWND );
	void Render();
	void Terminate();
};

