#pragma once

class ColorShader
{
public:
	ColorShader( ) noexcept;

	void Initialize( ID3D11Device*, HWND );
	void Shutdown( );
	void Render( ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX );

private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	void InitializeShader( ID3D11Device*, HWND, WCHAR*, WCHAR* );
	void ShutdownShader( );
	void OutputShaderErrorMessage( ID3DBlob*, HWND, WCHAR* );
	void RenderShader( ID3D11DeviceContext*, int );
	void SetShaderParameters( ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX );

	UINT mShaderFlag;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mFragmentShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mMatrixBuffer;
};