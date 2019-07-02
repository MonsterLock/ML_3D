#include "Global.h"
#include "FontShader.h"

void FontShader::InitializeShader( ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* fsFilename )
{
	// Initialize the pointers this function will use to null.
	ID3DBlob
		*errorMessage = nullptr,
		*vertexShaderBuffer = nullptr,
		*fragmentShaderBuffer = nullptr;

	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS | D3D10_SHADER_ENABLE_STRICTNESS;
	#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	#endif

	// Compile the vertex shader code.
	TESTRESULT( FAILED( D3DCompileFromFile( vsFilename, nullptr, nullptr, "FontVertexShader", "vs_5_0", flags, 0, &vertexShaderBuffer, &errorMessage ) ) );

	// Compile the pixel shader code.
	TESTRESULT( FAILED( D3DCompileFromFile( fsFilename, nullptr, nullptr, "FontPixelShader", "ps_5_0", flags, 0, &fragmentShaderBuffer, &errorMessage ) ) );

	// Create the vertex shader from the buffer.
	TESTRESULT( FAILED( device->CreateVertexShader( vertexShaderBuffer->GetBufferPointer( ), vertexShaderBuffer->GetBufferSize( ), NULL, mVertexShader.GetAddressOf() ) ) );

	// Create the vertex shader from the buffer.
	TESTRESULT( FAILED( device->CreatePixelShader( fragmentShaderBuffer->GetBufferPointer( ), fragmentShaderBuffer->GetBufferSize( ), NULL, mFragmentShader.GetAddressOf( ) ) ) );

	// Create the vertex input layout description.
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
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

	// Get a count of the elements in the layout.
	UINT numElements = sizeof( polygonLayout ) / sizeof( polygonLayout[0] );

	// Create the vertex input layout.
	TESTRESULT( FAILED( device->CreateInputLayout( polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer( ), vertexShaderBuffer->GetBufferSize( ), mLayout.GetAddressOf( ) ) ) );

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	vertexShaderBuffer->Release( );
	vertexShaderBuffer = nullptr;
	fragmentShaderBuffer->Release( );
	fragmentShaderBuffer = nullptr;

	// Setup the description of the dynamic constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC constantBufferDesc;
	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.ByteWidth = sizeof( ConstantBufferType );
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDesc.MiscFlags = 0;
	constantBufferDesc.StructureByteStride = 0;
	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	TESTRESULT( FAILED( device->CreateBuffer( &constantBufferDesc, NULL, mConstantBuffer.GetAddressOf( ) ) ) );

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

	// Setup the description of the dynamic pixel constant buffer that is in the pixel shader.
	D3D11_BUFFER_DESC pixelBufferDesc;
	pixelBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	pixelBufferDesc.ByteWidth = sizeof( PixelBufferType );
	pixelBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	pixelBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pixelBufferDesc.MiscFlags = 0;
	pixelBufferDesc.StructureByteStride = 0;
	// Create the pixel constant buffer pointer so we can access the pixel shader constant buffer from within this class.
	TESTRESULT( FAILED( device->CreateBuffer( &pixelBufferDesc, NULL, mFragmentBuffer.GetAddressOf( ) ) ) );
}

void FontShader::ShutdownShader( )
{
	mVertexShader.Reset();
	mFragmentShader.Reset();
	mLayout.Reset();
	mConstantBuffer.Reset( );
	mSampleState.Reset();
	mFragmentBuffer.Reset();
}

void FontShader::OutputShaderErrorMessage( ID3DBlob* errorMessage, HWND hwnd, WCHAR* shaderFilename )
{
	char* compileErrors;
	unsigned long bufferSize, i;
	std::ofstream fout;

	// Get a pointer to the error message text buffer.
	compileErrors = ( char* )( errorMessage->GetBufferPointer( ) );

	// Get the length of the message.
	bufferSize = static_cast<UINT>( errorMessage->GetBufferSize( ));

	// Open a file to write the error message to.
	fout.open( "shader-error.txt" );

	// Write out the error message.
	for( i = 0; i < bufferSize; i++ )
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close( );

	// Release the error message.
	errorMessage->Release( );
	errorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox( hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK );
}

void FontShader::SetShaderParameters( ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, XMFLOAT4 pixelColor )
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ConstantBufferType* dataPtr;
	PixelBufferType* dataPtr2;

	// Lock the constant buffer so it can be written to.
	TESTRESULT( FAILED( deviceContext->Map( mConstantBuffer.Get( ), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource ) ) );

	// Get a pointer to the data in the constant buffer.
	dataPtr = ( ConstantBufferType* )mappedResource.pData;

	// Transpose the matrices to prepare them for the shader.
	worldMatrix = XMMatrixTranspose( worldMatrix );
	viewMatrix = XMMatrixTranspose( viewMatrix );
	projectionMatrix = XMMatrixTranspose( projectionMatrix );

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer.
	deviceContext->Unmap( mConstantBuffer.Get( ), 0 );

	// Set the position of the constant buffer in the vertex shader.
	UINT bufferNumber = 0;

	// Now set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers( bufferNumber, 1, mConstantBuffer.GetAddressOf( ) );

	// Set shader texture resource in the pixel shader.
	deviceContext->PSSetShaderResources( 0, 1, &texture );

	// Lock the pixel constant buffer so it can be written to.
	TESTRESULT( FAILED( deviceContext->Map( mFragmentBuffer.Get( ), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource ) ) );

	// Get a pointer to the data in the pixel constant buffer.
	dataPtr2 = ( PixelBufferType* )mappedResource.pData;

	// Copy the pixel color into the pixel constant buffer.
	dataPtr2->pixelColor = pixelColor;

	// Unlock the pixel constant buffer.
	deviceContext->Unmap( mFragmentBuffer.Get( ), 0 );

	// Set the position of the pixel constant buffer in the pixel shader.
	bufferNumber = 0;

	// Now set the pixel constant buffer in the pixel shader with the updated value.
	deviceContext->PSSetConstantBuffers( bufferNumber, 1, mFragmentBuffer.GetAddressOf( ) );
}

void FontShader::RenderShader( ID3D11DeviceContext* deviceContext, int indexCount )
{
	// Set the vertex input layout.
	deviceContext->IASetInputLayout( mLayout.Get( ) );

	// Set the vertex and pixel shaders that will be used to render the triangles.
	deviceContext->VSSetShader( mVertexShader.Get(), NULL, 0 );
	deviceContext->PSSetShader( mFragmentShader.Get( ), NULL, 0 );

	// Set the sampler state in the pixel shader.
	deviceContext->PSSetSamplers( 0, 1, mSampleState.GetAddressOf( ) );

	// Render the triangles.
	deviceContext->DrawIndexed( indexCount, 0, 0 );
}

FontShader::FontShader( )
	:
	mVertexShader( nullptr ),
	mFragmentShader( nullptr ),
	mLayout( nullptr ),
	mConstantBuffer( nullptr ),
	mSampleState( nullptr ),
	mFragmentBuffer( nullptr )
{ }

void FontShader::Initialize( ID3D11Device* device, HWND hwnd )
{
	// Initialize the vertex and pixel shaders.
	InitializeShader( device, hwnd, const_cast< WCHAR* >( L"C:..\\font.vs" ), const_cast< WCHAR* >( L"C:..\\font.fs" ) );
}

void FontShader::Shutdown( )
{
	// Shutdown the vertex and pixel shaders as well as the related objects.
	ShutdownShader( );
}

void FontShader::Render( ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
						 XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, XMFLOAT4 pixelColor )
{
	// Set the shader parameters that it will use for rendering.
	SetShaderParameters( deviceContext, worldMatrix, viewMatrix, projectionMatrix, texture, pixelColor );
	// Now render the prepared buffers with the shader.
	RenderShader( deviceContext, indexCount );
}
