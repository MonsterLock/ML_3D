#pragma once

class GraphicsD3D
{
private:
	HWND												mHwnd;
	UINT												mWidth, mHeight;
	D3D_FEATURE_LEVEL									mFeatureLevel;
	Microsoft::WRL::ComPtr<ID3D11Device>				mDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			mContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain>				mSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		mRenderTargetView;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>		mDepthStencilState;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>		mDepthStencilStateDisabled;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		mDepthStencilView;

	Microsoft::WRL::ComPtr<ID3D11Texture2D>				mDepthStencilBuffer;

	Microsoft::WRL::ComPtr<ID3D11RasterizerState>*		mRasterStates;

	Microsoft::WRL::ComPtr<ID3D11BlendState>*			mBlendStates;

	Microsoft::WRL::ComPtr<ID3D11Buffer>*				mCbApp;
	Microsoft::WRL::ComPtr<ID3D11Buffer>*				mCbFrame;
	Microsoft::WRL::ComPtr<ID3D11Buffer>*				mCbObject;
	Microsoft::WRL::ComPtr<ID3D11Buffer>*				mCbCs;
	Microsoft::WRL::ComPtr<ID3D11Buffer>*				mCbDs;
	Microsoft::WRL::ComPtr<ID3D11Buffer>*				mCbGs;
	Microsoft::WRL::ComPtr<ID3D11Buffer>*				mCbHs;
	Microsoft::WRL::ComPtr<ID3D11Buffer>*				mCbPs;
	Microsoft::WRL::ComPtr<ID3D11Buffer>*				mCbVs;
	Microsoft::WRL::ComPtr<ID3D11Buffer>*				mCbVertices;
	Microsoft::WRL::ComPtr<ID3D11Buffer>*				mCbIndices;
	D3D11_PRIMITIVE_TOPOLOGY*							mTopologies;
	UINT*												mStrides;

	bool CreateDevice( );
	bool CreateResources( );
	void OnDeviceLost( );

	bool CreateDepthBuffer( ID3D11Texture2D**, UINT width, UINT height );
	bool CreateDepthStencil( ID3D11DepthStencilState**, bool );
	bool CreateResterizeState( ID3D11RasterizerState**, D3D11_FILL_MODE  fillMode, D3D11_CULL_MODE  cullMode );
	bool CreateBlendState(ID3D11BlendState**, bool, D3D11_BLEND, D3D11_BLEND );

	void ShutdownRasterStates( );
	void ShutdownBlendStates( );

public:
	GraphicsD3D( ) noexcept;
	bool Initialize( HWND, const UINT width, const UINT height );
	void BeginUpdate( XMVECTORF32 );
	void EndUpdate( );
	void Shutdown( );

	ID3D11Device* GetDevice( );
	ID3D11DeviceContext* GetContext( );
	ID3D11DepthStencilView* GetDepthStencilView( );

	void EnableZ( );
	void DisableZ( );
	void SetRasterState( UINT );
	void SetBlendState( UINT );
	void SetRenderTarget( );
	template <typename T>
	bool SaveMesh( D3D11_PRIMITIVE_TOPOLOGY, UINT, T*, UINT, UINT*, UINT );
	void LoadMesh( UINT );
	bool CreateBuffer( D3D11_USAGE, UINT, ID3D11Buffer** );
	bool Update
};

