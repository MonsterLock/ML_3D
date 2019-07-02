#pragma once
#include "Texture.h"

class Bitmap
{
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

	void InitializeBuffers( ID3D11Device* );
	void ShutdownBuffers( );
	void UpdateBuffers( ID3D11DeviceContext*, int, int );
	void RenderBuffers( ID3D11DeviceContext* );

	void LoadTexture( ID3D11Device*, const wchar_t* );
	void ReleaseTexture( );

	Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer;
	std::shared_ptr< Texture > mTexture;
	int
		mVertexCount, mIndexCount,
		mScreenWidth, mScreenHeight,
		mBitmapWidth, mBitmapHeight,
		mPreviousPosX, mPreviousPosY;

public:
	Bitmap( );
	void Initialize( ID3D11Device*, int, int, const wchar_t*, int, int );
	void Shutdown( );
	void Render( ID3D11DeviceContext*, int, int );
	int GetIndexCount( );
	ID3D11ShaderResourceView* GetTexture( );
};

