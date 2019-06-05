#pragma once
#include <WinSDKVer.h>
//#define _WIN32_WINNT 0x0601
#include <SDKDDKVer.h>

// Use the C++ standard templated min/max
#define NOMINMAX

// DirectX apps don't need GDI
#define NODRAWTEXT
#define NOGDI
#define NOBITMAP

// Include <mcx.h> if you need this
#define NOMCX

// Include <winsvc.h> if you need this
#define NOSERVICE

// WinHelp is deprecated
#define NOHELP

#include "Renderer.h"

#include <wrl/client.h>

#include <d3d11_1.h>
#include <dxgi1_2.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include <algorithm>
#include <exception>
#include <memory>
#include <stdexcept>

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

