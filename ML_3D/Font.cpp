#include "Global.h"
#include "Font.h"

void Font::LoadFontData( const wchar_t* filename )
{
	std::wifstream fin;
	wchar_t temp;

	// Create the font spacing buffer.
	mFont = new FontType[95];
	TESTRESULT( !mFont );

	// Read in the font size and spacing between chars.
	fin.open( filename );
	TESTRESULT( fin.fail( ) );

	// Read in the 95 used ascii characters for text.
	for( int i = 0; i < 95; i++ )
	{
		fin.get( temp );
		while( temp != ' ' )
		{
			fin.get( temp );
		}
		fin.get( temp );
		while( temp != ' ' )
		{
			fin.get( temp );
		}

		fin >> mFont[i].left;
		fin >> mFont[i].right;
		fin >> mFont[i].size;
	}

	// Close the file.
	fin.close( );
}

void Font::ReleaseFontData( )
{
	// Release the font data array.
	if( mFont )
	{
		delete[] mFont;
		mFont = nullptr;
	}
}

void Font::LoadTexture( ID3D11Device* device, ID3D11DeviceContext * deviceContext, const wchar_t* filename )
{
	// Create the texture object.
	mTexture = std::shared_ptr<Texture>( new Texture( ) );
	TESTRESULT( !mTexture );

	// Initialize the texture object.
	mTexture->Initialize( device, filename );
}

void Font::ReleaseTexture( )
{
	return;
}

Font::Font( )
	:
	mFont( nullptr ),
	mTexture( nullptr )
{ }

void Font::Initialize( ID3D11Device* device, ID3D11DeviceContext * deviceContext, const wchar_t* fontFilename, const wchar_t* textureFilename )
{
	// Load in the text file containing the font data.
	LoadFontData( fontFilename );

	// Load the texture that has the font characters on it.
	LoadTexture( device, deviceContext, textureFilename );
}

void Font::Shutdown( )
{
	// Release the font texture.
	ReleaseTexture( );

	// Release the font data.
	ReleaseFontData( );
}

ID3D11ShaderResourceView * Font::GetTexture( )
{
	return mTexture->GetTexture( );
}

void Font::BuildVertexArray( void* vertices, const char* sentence, float drawX, float drawY )
{
	VertexType* vertexPtr;
	int numLetters, index, letter;


	// Coerce the input vertices into a VertexType structure.
	vertexPtr = ( VertexType* )vertices;

	// Get the number of letters in the sentence.
	numLetters = ( int )strlen( sentence );

	// Initialize the index to the vertex array.
	index = 0;

	// Draw each letter onto a quad.
	for( int i = 0; i < numLetters; i++ )
	{
		letter = ( ( int )sentence[i] ) - 32;

		// If the letter is a space then just move over three pixels.
		if( letter == 0 )
		{
			drawX = drawX + 3.0f;
		}
		else
		{
			// First triangle in quad.
			vertexPtr[index].position = XMFLOAT3( drawX, drawY, 0.0f );  // Top left.
			vertexPtr[index].texture = XMFLOAT2( mFont[letter].left, 0.0f );
			index++;

			vertexPtr[index].position = XMFLOAT3( ( drawX + mFont[letter].size ), ( drawY - 16 ), 0.0f );  // Bottom right.
			vertexPtr[index].texture = XMFLOAT2( mFont[letter].right, 1.0f );
			index++;

			vertexPtr[index].position = XMFLOAT3( drawX, ( drawY - 16 ), 0.0f );  // Bottom left.
			vertexPtr[index].texture = XMFLOAT2( mFont[letter].left, 1.0f );
			index++;

			// Second triangle in quad.
			vertexPtr[index].position = XMFLOAT3( drawX, drawY, 0.0f );  // Top left.
			vertexPtr[index].texture = XMFLOAT2( mFont[letter].left, 0.0f );
			index++;

			vertexPtr[index].position = XMFLOAT3( drawX + mFont[letter].size, drawY, 0.0f );  // Top right.
			vertexPtr[index].texture = XMFLOAT2( mFont[letter].right, 0.0f );
			index++;

			vertexPtr[index].position = XMFLOAT3( ( drawX + mFont[letter].size ), ( drawY - 16 ), 0.0f );  // Bottom right.
			vertexPtr[index].texture = XMFLOAT2( mFont[letter].right, 1.0f );
			index++;

			// Update the x location for drawing by the size of the letter and one pixel.
			drawX = drawX + mFont[letter].size + 1.0f;
		}
	}
}
