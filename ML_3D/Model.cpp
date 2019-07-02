#include "Global.h"
#include "Model.h"

Model::Model( ) noexcept
	:
	mVertexBuffer( nullptr ),
	mIndexBuffer( nullptr ),
	mModel(nullptr)
{ }

void Model::Initialize( ID3D11Device* device )
{
	// Initialize the vertex and index buffers.
	InitializeBuffers( device );
}

void Model::Initialize( ID3D11Device* device, char* modelFilename, const wchar_t* textureFilename )
{
	// Load the model data.
	LoadModel( modelFilename );

	// Initialize the vertex and index buffers.
	InitializeBuffers( device );

	// Load the texture for this model.
	LoadTexture( device, textureFilename );
}

void Model::Shutdown( )
{
	// Release the model texture.
	ReleaseTexture( );

	// Shutdown the vertex and index buffers;
	ShutdownBuffers( );

	// Release the model data.
	ReleaseModel( );
}

void Model::Render( ID3D11DeviceContext * deviceContext )
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers( deviceContext );
}

int Model::GetIndexCount( )
{
	return mIndexCount;
}

ID3D11ShaderResourceView * Model::GetTexture( )
{
	return mTexture->GetTexture( );
}

void Model::InitializeBuffers( ID3D11Device * device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	// Create the vertex array.
	vertices = new VertexType[mVertexCount];
	TESTRESULT( !vertices );

	// Create the index array.
	indices = new unsigned long[mIndexCount];
	TESTRESULT( !indices );

	// Load the vertex array and index array with data.
	for( int i = 0; i < mVertexCount; i++ )
	{
		vertices[i].position = XMFLOAT3( mModel[i].x, mModel[i].y, mModel[i].z );
		vertices[i].texture = XMFLOAT2( mModel[i].tu, mModel[i].tv );
		vertices[i].normal = XMFLOAT3( mModel[i].nx, mModel[i].ny, mModel[i].nz );

		indices[i] = i;
	}

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof( VertexType ) * mVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the sub-resource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	TESTRESULT( FAILED( device->CreateBuffer( &vertexBufferDesc, &vertexData, mVertexBuffer.GetAddressOf( ) ) ) );

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof( unsigned long ) * mIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the sub-resource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	TESTRESULT( FAILED( device->CreateBuffer( &indexBufferDesc, &indexData, mIndexBuffer.GetAddressOf() ) ) );

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = nullptr;

	delete[] indices;
	indices = nullptr;
}

void Model::ShutdownBuffers( )
{
	mIndexBuffer.Reset( );
	mVertexBuffer.Reset( );
}

void Model::RenderBuffers( ID3D11DeviceContext * deviceContext)
{
	unsigned int
		stride,
		offset;

	// Set vertex buffer stride and offset.
	stride = sizeof( VertexType );
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers( 0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset );

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer( mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0 );

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
}

void Model::LoadTexture( ID3D11Device* device, const wchar_t* filename )
{
	// Create the texture object.
	mTexture = std::shared_ptr<Texture>( new Texture( ) );

	// Initialize the texture object.
	mTexture->Initialize( device, filename );
}

void Model::ReleaseTexture( )
{
	if( mTexture )
	{
		mTexture->Shutdown( );
	}
}

void Model::LoadModel( char * filename)
{
	std::ifstream fin;
	char input;

	// Open the model file.
	fin.open( filename );

	// If it could not open the file then exit.
	TESTRESULT( fin.fail( ) );

	// Read up to the value of vertex count.
	fin.get( input );
	while( input != ':' )
	{
		fin.get( input );
	}

	// Read in the vertex count.
	fin >> mVertexCount;

	// Set the number of indices to be the same as the vertex count.
	mIndexCount = mVertexCount;

	// Create the model using the vertex count that was read in.
	mModel = new ModelType[mVertexCount];

	TESTRESULT( !mModel );

	// Read up the beginning of the data.
	fin.get( input );
	while( input != ':' )
	{
		fin.get( input );
	}
	fin.get( input );
	fin.get( input );

	// Read in the vertex data.
	for( int i = 0; i < mVertexCount; i++ )
	{
		fin >> mModel[i].x >> mModel[i].y >> mModel[i].z;
		fin >> mModel[i].tu >> mModel[i].tv;
		fin >> mModel[i].nx >> mModel[i].ny >> mModel[i].nz;
	}

	// Close the model file.
	fin.close( );
}

void Model::ReleaseModel( )
{
	if( mModel )
	{
		delete[] mModel;
		mModel = nullptr;
	}
}
