#include "Global.h"
#include "Texture.h"

Texture::Texture( )
	:
	mTargaData( nullptr ),
	mTexture( nullptr ),
	mTextureView( nullptr )
{ }

void Texture::Initialize( ID3D11Device * device, const wchar_t * filename )
{
	TESTRESULT( FAILED( CreateWICTextureFromFile( device, filename, nullptr, mTextureView.GetAddressOf( ) ) ) );
}

void Texture::Shutdown( )
{
	mTextureView.Reset( );
	mTexture.Reset( );
	if( mTargaData )
	{
		delete[] mTargaData;
		mTargaData = nullptr;
	}
}

ID3D11ShaderResourceView * Texture::GetTexture( )
{
	return mTextureView.Get();
}
