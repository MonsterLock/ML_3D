#pragma once
class FbxLoader
{
	FbxManager* mFbxManager;
	FbxScene* mFbxScene;
	std::filesystem::path mIn, mOut;
	bool mIsCompressed;

public:
	FbxLoader( ) noexcept;
	bool Initialize( LPCWSTR, LPCWSTR, bool );
	bool LoadScene( );
	void GetContent( );
	void GetContent( FbxNode* pNode );
	void GetMesh( FbxNode* pNode );
	bool GetPolygons( FbxMesh* pMesh );
	void Shutdown( );
};
