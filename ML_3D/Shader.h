#pragma once
class Shader
{
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct LightBufferType
	{
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightDirection;
		float padding;  // Added extra padding so structure is a multiple of 16 for CreateBuffer function requirements.
	};

public:
	Shader( ) noexcept;

	void Initialize( ID3D11Device*, HWND );
	void Shutdown( );
	void Render( ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4 );

private:
	void InitializeShader( ID3D11Device*, HWND, WCHAR*, WCHAR* );
	void ShutdownShader( );
	void OutputShaderErrorMessage( ID3D10Blob*, HWND, WCHAR* );
	void SetShaderParameters( ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4 );
	void RenderShader( ID3D11DeviceContext*, int );

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mFragmentShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mMatrixBuffer;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> mSampleState;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mLightBuffer;
};