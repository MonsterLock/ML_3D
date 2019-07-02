#pragma once
#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"

class Texture
{
	struct TargaHeader
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};

	unsigned char* mTargaData;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTextureView;

public:
	Texture( );
	void Initialize( ID3D11Device*, const wchar_t* );
	void Shutdown( );
	ID3D11ShaderResourceView* GetTexture( );
};