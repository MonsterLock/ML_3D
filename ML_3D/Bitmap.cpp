#include "Global.h"
#include "Bitmap.h"

void Bitmap::InitializeBuffers( ID3D11Device * device )
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC
		vertexBufferDesc,
		indexBufferDesc;
	D3D11_SUBRESOURCE_DATA
		vertexData,
		indexData;

	// Set the number of vertices in the vertex array.
	mVertexCount = 6;

	// Set the number of indices in the index array.
	mIndexCount = mVertexCount;

	// Create the vertex array.
	vertices = new VertexType[mVertexCount];
	TESTRESULT( !vertices );

	// Create the index array.
	indices = new unsigned long[mIndexCount];
	TESTRESULT( !indices );

	// Initialize vertex array to zeros at first.
	memset( vertices, 0, ( sizeof( VertexType ) * mVertexCount ) );

	// Load the index array with data.
	for( int i = 0; i < mIndexCount; i++ )
	{
		indices[i] = i;
	}

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof( VertexType ) * mVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	TESTRESULT( FAILED( device->CreateBuffer( &vertexBufferDesc, &vertexData, mVertexBuffer.GetAddressOf() ) ) );

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof( unsigned long ) * mIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	TESTRESULT( FAILED( device->CreateBuffer( &indexBufferDesc, &indexData, mIndexBuffer.GetAddressOf( ) ) ) );

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = nullptr;

	delete[] indices;
	indices = nullptr;
}

void Bitmap::ShutdownBuffers( )
{
	mVertexBuffer.Reset( );
	mIndexBuffer.Reset( );
}

void Bitmap::UpdateBuffers( ID3D11DeviceContext* deviceContext, int positionX, int positionY )
{
	float left, right, top, bottom;
	VertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;

	// If the position we are rendering this bitmap to has not changed then don't update the vertex buffer since it
	// currently has the correct parameters.
	if( ( positionX == mPreviousPosX ) && ( positionY == mPreviousPosY ) )
	{
		return;
	}

	// If it has changed then update the position it is being rendered to.
	mPreviousPosX = positionX;
	mPreviousPosY = positionY;

	// Calculate the screen coordinates of the left side of the bitmap.
	left = ( float )( ( mScreenWidth / 2 ) * -1 ) + ( float )positionX;

	// Calculate the screen coordinates of the right side of the bitmap.
	right = left + ( float )mBitmapWidth;

	// Calculate the screen coordinates of the top of the bitmap.
	top = ( float )( mScreenHeight / 2 ) - ( float )positionY;

	// Calculate the screen coordinates of the bottom of the bitmap.
	bottom = top - ( float )mBitmapHeight;

	// Create the vertex array.
	vertices = new VertexType[mVertexCount];
	TESTRESULT( !vertices );

	// Load the vertex array with data.
	// First triangle.
	vertices[0].position = XMFLOAT3( left, top, 0.0f );  // Top left.
	vertices[0].texture = XMFLOAT2( 0.0f, 0.0f );

	vertices[1].position = XMFLOAT3( right, bottom, 0.0f );  // Bottom right.
	vertices[1].texture = XMFLOAT2( 1.0f, 1.0f );

	vertices[2].position = XMFLOAT3( left, bottom, 0.0f );  // Bottom left.
	vertices[2].texture = XMFLOAT2( 0.0f, 1.0f );

	// Second triangle.
	vertices[3].position = XMFLOAT3( left, top, 0.0f );  // Top left.
	vertices[3].texture = XMFLOAT2( 0.0f, 0.0f );

	vertices[4].position = XMFLOAT3( right, top, 0.0f );  // Top right.
	vertices[4].texture = XMFLOAT2( 1.0f, 0.0f );

	vertices[5].position = XMFLOAT3( right, bottom, 0.0f );  // Bottom right.
	vertices[5].texture = XMFLOAT2( 1.0f, 1.0f );

	// Lock the vertex buffer so it can be written to.
	TESTRESULT( FAILED( deviceContext->Map( mVertexBuffer.Get( ), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource ) ) );

	// Get a pointer to the data in the vertex buffer.
	verticesPtr = ( VertexType* )mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy( verticesPtr, ( void* )vertices, ( sizeof( VertexType ) * mVertexCount ) );

	// Unlock the vertex buffer.
	deviceContext->Unmap( mVertexBuffer.Get(), 0 );

	// Release the vertex array as it is no longer needed.
	delete[] vertices;
	vertices = nullptr;
}

void Bitmap::RenderBuffers( ID3D11DeviceContext * deviceContext )
{
	// Set vertex buffer stride and offset.
	unsigned int
		stride = sizeof( VertexType ),
		offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers( 0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset );

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer( mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0 );

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
}

void Bitmap::LoadTexture( ID3D11Device * device, const wchar_t * filename )
{
	// Create the texture object.
	mTexture = std::shared_ptr<Texture>( new Texture( ) );
	TESTRESULT( !mTexture );

	// Initialize the texture object.
	mTexture->Initialize( device, filename );
}

void Bitmap::ReleaseTexture( )
{
	return;
}

Bitmap::Bitmap( )
	:
	mVertexBuffer( nullptr ),
	mIndexBuffer( nullptr )
{ }

void Bitmap::Initialize( ID3D11Device* device, int screenWidth, int screenHeight, const wchar_t* textureFilename, int bitmapWidth, int bitmapHeight )
{
	// Store the screen size.
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	// Store the size in pixels that this bitmap should be rendered at.
	mBitmapWidth = bitmapWidth;
	mBitmapHeight = bitmapHeight;

	// Initialize the previous rendering position to negative one.
	mPreviousPosX = -1;
	mPreviousPosY = -1;

	// Initialize the vertex and index buffers.
	InitializeBuffers( device );

	// Load the texture for this model.
	LoadTexture( device, textureFilename );
}

void Bitmap::Shutdown( )
{
	// Release the model texture.
	ReleaseTexture( );

	// Shutdown the vertex and index buffers.
	ShutdownBuffers( );
}

void Bitmap::Render( ID3D11DeviceContext* deviceContext, int positionX, int positionY )
{
	// Re-build the dynamic vertex buffer for rendering to possibly a different location on the screen.
	UpdateBuffers( deviceContext, positionX, positionY );
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers( deviceContext );
}

int Bitmap::GetIndexCount( )
{
	return mIndexCount;
}

ID3D11ShaderResourceView * Bitmap::GetTexture( )
{
	return mTexture->GetTexture( );
}