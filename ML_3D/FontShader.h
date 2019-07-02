#pragma once
#include <fstream>

class FontShader
{
	struct ConstantBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct PixelBufferType
	{
		XMFLOAT4 pixelColor;
	};

	void InitializeShader( ID3D11Device*, HWND, WCHAR*, WCHAR* );
	void ShutdownShader( );
	void OutputShaderErrorMessage( ID3DBlob*, HWND, WCHAR* );

	void SetShaderParameters( ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT4 );
	void RenderShader( ID3D11DeviceContext*, int );

	Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mFragmentShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mConstantBuffer;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> mSampleState;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mFragmentBuffer;

public:
	FontShader( );
	void Initialize( ID3D11Device*, HWND );
	void Shutdown( );
	void Render( ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT4 );
};

