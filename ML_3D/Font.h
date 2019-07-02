#pragma once
#include <fstream>
#include "Texture.h"

class Font
{
	struct FontType
	{
		float left, right;
		int size;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

	void LoadFontData( const wchar_t* );
	void ReleaseFontData( );
	void LoadTexture( ID3D11Device*, ID3D11DeviceContext *, const wchar_t* );
	void ReleaseTexture( );
	FontType* mFont;
	std::shared_ptr<Texture> mTexture;

public:
	Font( );
	void Initialize( ID3D11Device*, ID3D11DeviceContext *, const wchar_t*, const wchar_t* );
	void Shutdown( );

	ID3D11ShaderResourceView* GetTexture( );
	void BuildVertexArray( void*, const char*, float, float );
};
