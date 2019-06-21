#pragma once

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

	unsigned char* m_targaData;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureView;

	bool LoadTarga( char*, int&, int& );

public:
	Texture( );
	void Initialize( ID3D11Device*, ID3D11DeviceContext*, char* );
	void Shutdown( );
	ID3D11ShaderResourceView* GetTexture( );
};

