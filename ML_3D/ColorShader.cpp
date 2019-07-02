#include "Global.h"
#include "ColorShader.h"
#include <fstream>

ColorShader::ColorShader( ) noexcept
	:
	mVertexShader( nullptr ),
	mFragmentShader( nullptr ),
	mLayout( nullptr ),
	mMatrixBuffer( nullptr )
{ }

void ColorShader::Initialize( ID3D11Device * device, HWND hwnd )
{
	// Initialize the vertex and pixel shaders.
	InitializeShader( device, hwnd, const_cast< WCHAR* >( L"C:..\\color.vs" ), const_cast< WCHAR* >( L"C:..\\color.fs" ) );
}

void ColorShader::Shutdown( )
{
	// Shutdown the vertex and pixel shaders as well as the related objects.
	ShutdownShader( );
}

void ColorShader::Render( ID3D11DeviceContext *deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix )
{
	// Set the shader parameters that it will use for rendering.
	SetShaderParameters( deviceContext, worldMatrix, viewMatrix, projectionMatrix );
	// Now render the prepared buffers with the shader.
	RenderShader( deviceContext, indexCount );
}

void ColorShader::InitializeShader( ID3D11Device * device, HWND hwnd, WCHAR * vsFilename, WCHAR * fsFilename )
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
	TESTRESULT( FAILED( D3DCompileFromFile( vsFilename, nullptr, nullptr, "ColorVertexShader", "vs_5_0", flags, 0, &vertexShaderBuffer, &errorMessage ) ) );

	// Compile the fragment shader code.
	TESTRESULT( FAILED( D3DCompileFromFile( fsFilename, nullptr, nullptr, "ColorFragmentShader", "ps_5_0", flags, 0, &fragmentShaderBuffer, &errorMessage ) ) );

	// Create the vertex shader from the buffer.
	TESTRESULT( FAILED( device->CreateVertexShader( vertexShaderBuffer->GetBufferPointer( ), vertexShaderBuffer->GetBufferSize( ), nullptr, mVertexShader.GetAddressOf( ) ) ) );

	// Create the fragment shader from the buffer.
	TESTRESULT( FAILED( device->CreatePixelShader( fragmentShaderBuffer->GetBufferPointer( ), fragmentShaderBuffer->GetBufferSize( ), nullptr, mFragmentShader.GetAddressOf( ) ) ) );

	// Create the vertex input layout description.
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	// This setup needs to match the VertexType structure in the Model class and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout.
	UINT numElements;
	numElements = sizeof( polygonLayout ) / sizeof( polygonLayout[0] );

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
}

void ColorShader::ShutdownShader( )
{
	mMatrixBuffer.Reset( );
	mLayout.Reset( );
	mFragmentShader.Reset( );
	mVertexShader.Reset( );
}

void ColorShader::OutputShaderErrorMessage( ID3DBlob * errorMessage, HWND hwnd, WCHAR * shaderFilename )
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

void ColorShader::SetShaderParameters( ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix )
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	UINT bufferNumber;

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
	bufferNumber = 0;

	// Finally set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers( bufferNumber, 1, mMatrixBuffer.GetAddressOf( ) );
}

void ColorShader::RenderShader( ID3D11DeviceContext * deviceContext, int indexCount )
{
	// Set the vertex input layout.
	deviceContext->IASetInputLayout( mLayout.Get( ) );

	// Set the vertex and fragment shaders that will be used to render this object.
	deviceContext->VSSetShader( mVertexShader.Get( ), nullptr, 0 );
	deviceContext->PSSetShader( mFragmentShader.Get( ), nullptr, 0 );

	// Render the triangle.
	deviceContext->DrawIndexed( indexCount, 0, 0 );
}
