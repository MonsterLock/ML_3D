#pragma once
#include "Font.h"
#include "FontShader.h"

class Text
{
	struct SentenceType
	{
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount, maxLength;
		float red, green, blue;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

	void InitializeSentence( SentenceType**, int, ID3D11Device* );
	void UpdateSentence( SentenceType*, char*, int, int, float, float, float, ID3D11DeviceContext* );
	void ReleaseSentence( SentenceType** );
	void RenderSentence( ID3D11DeviceContext*, SentenceType*, XMMATRIX, XMMATRIX );

	Font* m_Font;
	FontShader* m_FontShader;
	int
		m_screenWidth,
		m_screenHeight;
	XMMATRIX m_baseViewMatrix;
	SentenceType
		* m_sentence1,
		* m_sentence2;

public:
	Text( );
	void Initialize( ID3D11Device*, ID3D11DeviceContext*, HWND, int, int, XMMATRIX );
	void Shutdown( );
	void Render( ID3D11DeviceContext*, XMMATRIX, XMMATRIX );
};

