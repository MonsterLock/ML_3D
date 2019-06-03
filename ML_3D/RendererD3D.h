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

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <wrl/client.h>

#include <d3d11_1.h>
#include <dxgi1_2.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include <algorithm>
#include <exception>
#include <memory>
#include <stdexcept>

class RendererD3D
{
	HWND												mHwnd;
	int
														m_outputWidth,
														m_outputHeight;
	D3D_FEATURE_LEVEL									m_featureLevel;
	Microsoft::WRL::ComPtr<ID3D11Device1>				m_d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1>		m_d3dContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain1>				m_swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		m_renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		m_depthStencilView;

	void CreateDevice();
	void CreateResources();
	void OnDeviceLost();

	void Clear();
	void Present();

public:
	RendererD3D() noexcept;

	// Initialization and management.
	void Inititalize( HWND window, int width, int height );
	void Render();
};

