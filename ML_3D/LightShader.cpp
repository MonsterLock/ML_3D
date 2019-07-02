#include "Global.h"
#include "LightShader.h"
#include <fstream>

LightShader::LightShader( ) noexcept
	:
	mVertexShader( nullptr ),
	mFragmentShader( nullptr ),
	mLayout( nullptr ),
	mMatrixBuffer( nullptr ),
	mSampleState( nullptr ),
	mCameraBuffer( nullptr ),
	mLightBuffer( nullptr )
{ }

void LightShader::Initialize( ID3D11Device * device, HWND hwnd )
{
	// Initialize the vertex and pixel shaders.
	InitializeShader( device, hwnd, const_cast< WCHAR* >( L"C:..\\light.vs" ), const_cast< WCHAR* >( L"C:..\\light.fs" ) );
}

void LightShader::Shutdown( )
{
	// Shutdown the vertex and pixel shaders as well as the related objects.
	ShutdownShader( );
}

void LightShader::Render( ID3D11DeviceContext *deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
					 ID3D11ShaderResourceView* texture,
					 XMFLOAT3 fLightDirection, XMFLOAT4 fDiffuseColor,
					 XMFLOAT4 ambientColor,
					 XMFLOAT3 cameraPosition, XMFLOAT4 specularColor, float specularPower )
{
	// Set the shader parameters that it will use for rendering.
	SetShaderParameters( deviceContext, worldMatrix, viewMatrix, projectionMatrix, texture, fLightDirection, fDiffuseColor, ambientColor, cameraPosition, specularColor, specularPower );
	// Now render the prepared buffers with the shader.
	RenderShader( deviceContext, indexCount );
}

void LightShader::InitializeShader( ID3D11Device * device, HWND hwnd, WCHAR * vsFilename, WCHAR * fsFilename )
{
	ID3DBlob
		*errorMessage = nullptr,
		*vertexShaderBuffer = nullptr,
		*fragmentShaderBuffer = nullptr;

	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS | D3D10_SHADER_ENABLE_STRICTNESS;
	#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	#endif

	// Compile the vertex shader code.
	TESTRESULT( FAILED( D3DCompileFromFile( vsFilename, nullptr, nullptr, "LightVertexShader", "vs_5_0", flags, 0, &vertexShaderBuffer, &errorMessage ) ) );

	// Compile the fragment shader code.
	TESTRESULT( FAILED( D3DCompileFromFile( fsFilename, nullptr, nullptr, "LightFragmentShader", "ps_5_0", flags, 0, &fragmentShaderBuffer, &errorMessage ) ) );

	// Create the vertex shader from the buffer.
	TESTRESULT( FAILED( device->CreateVertexShader( vertexShaderBuffer->GetBufferPointer( ), vertexShaderBuffer->GetBufferSize( ), nullptr, mVertexShader.GetAddressOf( ) ) ) );

	// Create the fragment shader from the buffer.
	TESTRESULT( FAILED( device->CreatePixelShader( fragmentShaderBuffer->GetBufferPointer( ), fragmentShaderBuffer->GetBufferSize( ), nullptr, mFragmentShader.GetAddressOf( ) ) ) );

	// Create the vertex input layout description.
	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	// This setup needs to match the VertexType structure in the Model class and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "NORMAL";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout.
	UINT numElements = sizeof( polygonLayout ) / sizeof( polygonLayout[0] );

	// Create the vertex input layout.
	TESTRESULT( FAILED( device->CreateInputLayout( polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer( ), vertexShaderBuffer->GetBufferSize( ), mLayout.GetAddressOf( ) ) ) );

	// Release what's no longer needed.
	vertexShaderBuffer->Release( );
	vertexShaderBuffer = nullptr;
	fragmentShaderBuffer->Release( );
	fragmentShaderBuffer = nullptr;

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof( MatrixBufferType );
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;
	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	TESTRESULT( FAILED( device->CreateBuffer( &matrixBufferDesc, nullptr, mMatrixBuffer.GetAddressOf( ) ) ) );

	// Create a texture sampler state description.
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	// Create the texture sampler state.
	TESTRESULT( FAILED( device->CreateSamplerState( &samplerDesc, mSampleState.GetAddressOf( ) ) ) );

	// Setup the description of the light dynamic constant buffer that is in the pixel shader.
	// Note that ByteWidth always needs to be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER or CreateBuffer will fail.
	D3D11_BUFFER_DESC lightBufferDesc;
	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof( LightBufferType );
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	TESTRESULT( FAILED( device->CreateBuffer( &lightBufferDesc, NULL, mLightBuffer.GetAddressOf( ) ) ) );

	// Setup the description of the camera dynamic constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC cameraBufferDesc;
	cameraBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cameraBufferDesc.ByteWidth = sizeof( CameraBufferType );
	cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cameraBufferDesc.MiscFlags = 0;
	cameraBufferDesc.StructureByteStride = 0;

	// Create the camera constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	TESTRESULT( FAILED( device->CreateBuffer( &cameraBufferDesc, NULL, &mCameraBuffer ) ) );
}

void LightShader::ShutdownShader( )
{
	mCameraBuffer.Reset( );
	mLightBuffer.Reset( );
	mSampleState.Reset( );
	mMatrixBuffer.Reset( );
	mLayout.Reset( );
	mFragmentShader.Reset( );
	mVertexShader.Reset( );
}

void LightShader::OutputShaderErrorMessage( ID3DBlob * errorMessage, HWND hwnd, WCHAR * shaderFilename )
{
	char* compileErrors;
	unsigned long long bufferSize;
	std::ofstream fout;

	// Get a pointer to the error message text buffer.
	compileErrors = reinterpret_cast< char* >( errorMessage->GetBufferPointer( ) );

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize( );

	// Open a file to write the error message to.
	fout.open( "shader-error.txt" );

	// Write out the error message.
	for( int i = 0; i < bufferSize; i++ )
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close( );

	// Release the error message.
	errorMessage->Release( );
	errorMessage = nullptr;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox( hwnd, L"Error compiling shader. Check shader-error.txt for message.", shaderFilename, MB_OK | MB_ICONERROR );
}

void LightShader::SetShaderParameters( ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
								  ID3D11ShaderResourceView* texture,
								  XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor,
								  XMFLOAT4 ambientColor,
								  XMFLOAT3 cameraPosition, XMFLOAT4 specularColor, float specularPower )
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	LightBufferType* dataPtr2;
	CameraBufferType* dataPtr3;

	// Transpose the matrices to prepare them for the shader.
	worldMatrix = XMMatrixTranspose( worldMatrix );
	viewMatrix = XMMatrixTranspose( viewMatrix );
	projectionMatrix = XMMatrixTranspose( projectionMatrix );

	// Lock the constant buffer so it can be written to.
	TESTRESULT( FAILED( deviceContext->Map( mMatrixBuffer.Get( ), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource ) ) );

	// Get a pointer to the data in the constant buffer.
	dataPtr = reinterpret_cast< MatrixBufferType* >( mappedResource.pData );

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer.
	deviceContext->Unmap( mMatrixBuffer.Get( ), 0 );

	// Set the position of the constant buffer in the vertex shader.
	UINT bufferNumber = 0;

	// Finally set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers( bufferNumber, 1, mMatrixBuffer.GetAddressOf( ) );

	// Lock the camera constant buffer so it can be written to.
	TESTRESULT( FAILED( deviceContext->Map( mCameraBuffer.Get( ), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource ) ) );

	// Get a pointer to the data in the constant buffer.
	dataPtr3 = ( CameraBufferType* )mappedResource.pData;

	// Copy the camera position into the constant buffer.
	dataPtr3->cameraPosition = cameraPosition;
	dataPtr3->padding = 0.0f;

	// Unlock the camera constant buffer.
	deviceContext->Unmap( mCameraBuffer.Get( ), 0 );

	// Set the position of the camera constant buffer in the vertex shader.
	bufferNumber = 1;

	// Now set the camera constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers( bufferNumber, 1, mCameraBuffer.GetAddressOf( ) );

	// Set shader texture resource in the pixel shader.
	deviceContext->PSSetShaderResources( 0, 1, &texture );

	// Lock the light constant buffer so it can be written to.
	TESTRESULT( FAILED( deviceContext->Map( mLightBuffer.Get( ), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource ) ) );

	// Get a pointer to the data in the constant buffer.
	dataPtr2 = reinterpret_cast< LightBufferType* >( mappedResource.pData );

	// Copy the lighting variables into the constant buffer.
	dataPtr2->ambientColor = ambientColor;
	dataPtr2->diffuseColor = diffuseColor;
	dataPtr2->lightDirection = lightDirection;
	dataPtr2->specularColor = specularColor;
	dataPtr2->specularPower = specularPower;

	// Unlock the constant buffer.
	deviceContext->Unmap( mLightBuffer.Get( ), 0 );

	// Set the position of the light constant buffer in the pixel shader.
	bufferNumber = 0;

	// Finally set the light constant buffer in the pixel shader with the updated values.
	deviceContext->PSSetConstantBuffers( bufferNumber, 1, mLightBuffer.GetAddressOf( ) );
}

void LightShader::RenderShader( ID3D11DeviceContext * deviceContext, int indexCount )
{
	// Set the vertex input layout.
	deviceContext->IASetInputLayout( mLayout.Get( ) );

	// Set the vertex and fragment shaders that will be used to render this object.
	deviceContext->VSSetShader( mVertexShader.Get( ), nullptr, 0 );
	deviceContext->PSSetShader( mFragmentShader.Get( ), nullptr, 0 );

	// Set the sampler state in the pixel shader.
	deviceContext->PSSetSamplers( 0, 1, mSampleState.GetAddressOf( ) );

	// Render the triangle.
	deviceContext->DrawIndexed( indexCount, 0, 0 );
}
