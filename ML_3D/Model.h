#pragma once
#include "texture.h"
#include <fstream>

class Model
{
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer;
	std::shared_ptr< Texture > mTexture;
	ModelType* mModel;
	int
		mVertexCount,
		mIndexCount;

	void InitializeBuffers( ID3D11Device* );
	void ShutdownBuffers( );
	void RenderBuffers( ID3D11DeviceContext* );
	void LoadTexture( ID3D11Device*, const wchar_t* );
	void ReleaseTexture( );
	void LoadModel( char* );
	void ReleaseModel( );

public:
	Model( ) noexcept;
	void Initialize( ID3D11Device * device );
	void Initialize( ID3D11Device*, char*, const wchar_t* );
	void Shutdown( );
	void Render( ID3D11DeviceContext* );
	int GetIndexCount( );
	ID3D11ShaderResourceView* GetTexture( );
};