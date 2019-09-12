#include "Global.h"
#include "FbxLoader.h"

FbxLoader::FbxLoader( )
	:
	mFbxManager( nullptr ),
	mFbxScene( nullptr )
{ }

bool FbxLoader::GetPolygons( FbxMesh * pMesh )
{
	int lPolygonCount = pMesh->GetPolygonCount( );
	FbxVector4* lControlPoints = pMesh->GetControlPoints( );

	std::vector< ml3d::Vertex_Type > verts;
	std::vector< UINT > inds;
	ml3d::Vertex_Type vert;
	UINT modelInfo = 0;
	bool isUnique = true;

	for( int i = 0; i < lPolygonCount; i++ )
	{
		int lPolygonSize = pMesh->GetPolygonSize( i );
		for( int j = 0, vertexId = 0; j < lPolygonSize; j++, vertexId++ )
		{
			int lControlPointIndex = pMesh->GetPolygonVertex( i, j );
			//------------------------------------------------------------------------------------------------ POSITIONS
			ZeroMemory( &vert, sizeof( vert ) );

			vert.pos = {
				static_cast< float >( lControlPoints[lControlPointIndex][0] ),
				static_cast< float >( lControlPoints[lControlPointIndex][1] ),
				static_cast< float >( lControlPoints[lControlPointIndex][2] ) };
			//------------------------------------------------------------------------------------------------ TEXTURES
			for( int l = 0; l < pMesh->GetElementUVCount( ); ++l )
			{
				FbxGeometryElementUV* leUV = pMesh->GetElementUV( l );
				switch( leUV->GetMappingMode( ) )
				{
					default:
						break;
					case FbxGeometryElement::eByControlPoint:
						switch( leUV->GetReferenceMode( ) )
						{
							case FbxGeometryElement::eDirect:
							{
								//------------------------------------------------------------------------------------------------
								vert.tex = {
									static_cast< float >( leUV->GetDirectArray( ).GetAt( lControlPointIndex )[0] ),
									static_cast< float >( leUV->GetDirectArray( ).GetAt( lControlPointIndex )[1] ) };
								//------------------------------------------------------------------------------------------------
							}
							break;
							case FbxGeometryElement::eIndexToDirect:
							{
								int id = leUV->GetIndexArray( ).GetAt( lControlPointIndex );
								//------------------------------------------------------------------------------------------------
								vert.tex = {
									static_cast< float >( leUV->GetDirectArray( ).GetAt( id )[0] ),
									static_cast< float >( leUV->GetDirectArray( ).GetAt( id )[1] ) };
								//------------------------------------------------------------------------------------------------
							}
							break;
							default:
								break;
						}
						break;
					case FbxGeometryElement::eByPolygonVertex:
					{
						int lTextureUVIndex = pMesh->GetTextureUVIndex( i, j );
						switch( leUV->GetReferenceMode( ) )
						{
							case FbxGeometryElement::eDirect:
							case FbxGeometryElement::eIndexToDirect:
							{
								//------------------------------------------------------------------------------------------------
								vert.tex = {
									static_cast< float >( leUV->GetDirectArray( ).GetAt( lTextureUVIndex )[0] ),
									static_cast< float >( leUV->GetDirectArray( ).GetAt( lTextureUVIndex )[1] ) };
								//------------------------------------------------------------------------------------------------
							}
							break;
							default:
								break;
						}
					}
					case FbxGeometryElement::eByPolygon:
					case FbxGeometryElement::eAllSame:
					case FbxGeometryElement::eNone:
						break;
				}
			}
			//------------------------------------------------------------------------------------------------ NORMALS
			for( int l = 0; l < pMesh->GetElementNormalCount( ); ++l )
			{
				FbxGeometryElementNormal* leNormal = pMesh->GetElementNormal( l );

				if( leNormal->GetMappingMode( ) == FbxGeometryElement::eByPolygonVertex )
				{
					switch( leNormal->GetReferenceMode( ) )
					{
						case FbxGeometryElement::eDirect:
						{
							//------------------------------------------------------------------------------------------------
							vert.nrm = {
								static_cast< float >( leNormal->GetDirectArray( ).GetAt( vertexId )[0] ),
								static_cast< float >( leNormal->GetDirectArray( ).GetAt( vertexId )[1] ),
								static_cast< float >( leNormal->GetDirectArray( ).GetAt( vertexId )[2] ) };
							//------------------------------------------------------------------------------------------------
						}
						break;
						case FbxGeometryElement::eIndexToDirect:
						{
							int id = leNormal->GetIndexArray( ).GetAt( vertexId );
							//------------------------------------------------------------------------------------------------
							vert.nrm = {
								static_cast< float >( leNormal->GetDirectArray( ).GetAt( id )[0] ),
								static_cast< float >( leNormal->GetDirectArray( ).GetAt( id )[1] ),
								static_cast< float >( leNormal->GetDirectArray( ).GetAt( id )[2] ) };
							//------------------------------------------------------------------------------------------------
						}
						break;
						default:
							break;
					}
				}
			}

			//------------------------------------------------------------------------------------------------ TANGENTS
			for( int l = 0; l < pMesh->GetElementTangentCount( ); ++l )
			{
				FbxGeometryElementTangent* leTangent = pMesh->GetElementTangent( l );

				if( leTangent->GetMappingMode( ) == FbxGeometryElement::eByPolygonVertex )
				{
					switch( leTangent->GetReferenceMode( ) )
					{
						case FbxGeometryElement::eDirect:
						{
							//------------------------------------------------------------------------------------------------
							vert.tan = {
								static_cast< float >( leTangent->GetDirectArray( ).GetAt( vertexId )[0] ),
								static_cast< float >( leTangent->GetDirectArray( ).GetAt( vertexId )[1] ),
								static_cast< float >( leTangent->GetDirectArray( ).GetAt( vertexId )[2] )
							};
							//------------------------------------------------------------------------------------------------
						}
						break;
						case FbxGeometryElement::eIndexToDirect:
						{
							int id = leTangent->GetIndexArray( ).GetAt( vertexId );
							//------------------------------------------------------------------------------------------------
							vert.tan = {
								static_cast< float >( leTangent->GetDirectArray( ).GetAt( id )[0] ),
								static_cast< float >( leTangent->GetDirectArray( ).GetAt( id )[1] ),
								static_cast< float >( leTangent->GetDirectArray( ).GetAt( id )[2] ) };
							//------------------------------------------------------------------------------------------------
						}
						break;
						default:
							break; // other reference modes not shown here!
					}
				}
			}
			//------------------------------------------------------------------------------------------------ BINORMALS
			for( int l = 0; l < pMesh->GetElementBinormalCount( ); ++l )
			{
				FbxGeometryElementBinormal* leBinormal = pMesh->GetElementBinormal( l );

				if( leBinormal->GetMappingMode( ) == FbxGeometryElement::eByPolygonVertex )
				{
					switch( leBinormal->GetReferenceMode( ) )
					{
						case FbxGeometryElement::eDirect:
						{
							//------------------------------------------------------------------------------------------------
							vert.btn = {
								static_cast< float >( leBinormal->GetDirectArray( ).GetAt( vertexId )[0] ),
								static_cast< float >( leBinormal->GetDirectArray( ).GetAt( vertexId )[1] ),
								static_cast< float >( leBinormal->GetDirectArray( ).GetAt( vertexId )[2] )
							};
							//------------------------------------------------------------------------------------------------
						}
						break;
						case FbxGeometryElement::eIndexToDirect:
						{
							int id = leBinormal->GetIndexArray( ).GetAt( vertexId );
							//------------------------------------------------------------------------------------------------
							vert.btn = {
								static_cast< float >( leBinormal->GetDirectArray( ).GetAt( id )[0] ),
								static_cast< float >( leBinormal->GetDirectArray( ).GetAt( id )[1] ),
								static_cast< float >( leBinormal->GetDirectArray( ).GetAt( id )[2] )
							};
							//------------------------------------------------------------------------------------------------
						}
						break;
						default:
							break; // other reference modes not shown here!
					}
				}
			}

			//------------------------------------------------------------------------------------------------ START COMPACTING

			if( !BitM::BitIsOn( modelInfo, 0 ) )
			{
				if( vert.pos.x || vert.pos.y || vert.pos.z )
				{
					BitM::BitOn( modelInfo, 0 );
				}
			}
			if( !BitM::BitIsOn( modelInfo, 1 ) )
			{
				if( vert.tex.x || vert.tex.y )
				{
					BitM::BitOn( modelInfo, 1 );
				}
			}
			if( !BitM::BitIsOn( modelInfo, 2 ) )
			{
				if( vert.nrm.x || vert.nrm.y || vert.nrm.z )
				{
					BitM::BitOn( modelInfo, 2 );
				}
			}
			if( !BitM::BitIsOn( modelInfo, 3 ) )
			{
				if( vert.tan.x || vert.tan.y || vert.tan.z )
				{
					BitM::BitOn( modelInfo, 3 );
				}
			}
			if( !BitM::BitIsOn( modelInfo, 4 ) )
			{
				if( vert.btn.x || vert.btn.y || vert.btn.z )
				{
					BitM::BitOn( modelInfo, 4 );
				}
			}

			switch( mIsCompressed )
			{
				case 0:
				{
					inds.push_back( static_cast< UINT >( verts.size( ) ) );
					verts.push_back( vert );
				}
				break;
				case 1:
				{
					isUnique = true;
					for( UINT k = 0; k < verts.size( ); k++ )
					{
						if( fabs( vert.pos.x - verts[k].pos.x ) < g_EPSILON &&
							fabs( vert.pos.y - verts[k].pos.y ) < g_EPSILON &&
							fabs( vert.pos.z - verts[k].pos.z ) < g_EPSILON &&
							fabs( vert.nrm.x - verts[k].nrm.x ) < g_EPSILON &&
							fabs( vert.nrm.y - verts[k].nrm.y ) < g_EPSILON &&
							fabs( vert.nrm.z - verts[k].nrm.z ) < g_EPSILON &&
							fabs( vert.tex.x - verts[k].tex.x ) < g_EPSILON &&
							fabs( vert.tex.y - verts[k].tex.y ) < g_EPSILON &&
							fabs( vert.tan.x - verts[k].tan.x ) < g_EPSILON &&
							fabs( vert.tan.y - verts[k].tan.y ) < g_EPSILON &&
							fabs( vert.tan.z - verts[k].tan.z ) < g_EPSILON &&
							fabs( vert.btn.x - verts[k].btn.x ) < g_EPSILON &&
							fabs( vert.btn.y - verts[k].btn.y ) < g_EPSILON &&
							fabs( vert.btn.z - verts[k].btn.z ) < g_EPSILON )
						{
							inds.push_back( k );
							isUnique = false;
							break;
						}
					}
					if( isUnique )
					{
						inds.push_back( static_cast< UINT >( verts.size( ) ) );
						verts.push_back( vert );
					}
				}
				break;
				default:
					break;
			}
		}// for polygonSize
	}// for polygonCount

	//------------------------------------------------------------------------------------------------ START FILE OUTPUT
	std::wstring temp = mIn.stem( );
	temp += L".bin";

	std::filesystem::path outFile = mOut;
	outFile /= std::filesystem::path( temp );
	std::ofstream bout( outFile, std::ios_base::binary );

	if( ISERROR2( !bout.is_open( ), Failed to create file. ) )
		return false;
	//------------------------------------------------------------------------------------------------ Vertex
	UINT vertexCount = static_cast< UINT >( verts.size( ) );
	BINOUT( vertexCount, UINT );
	for( UINT i = 0; i < vertexCount; i++ )
	{
		BINOUT( verts[i].pos.x, float );
		BINOUT( verts[i].pos.y, float );
		BINOUT( verts[i].pos.z, float );

		BINOUT( verts[i].tex.x, float );
		BINOUT( verts[i].tex.y, float );

		BINOUT( verts[i].nrm.x, float );
		BINOUT( verts[i].nrm.y, float );
		BINOUT( verts[i].nrm.z, float );

		BINOUT( verts[i].tan.x, float );
		BINOUT( verts[i].tan.y, float );
		BINOUT( verts[i].tan.z, float );

		BINOUT( verts[i].btn.x, float );
		BINOUT( verts[i].btn.y, float );
		BINOUT( verts[i].btn.z, float );
	}
	//------------------------------------------------------------------------------------------------ Index
	UINT indexCount = static_cast< UINT >( inds.size( ) );
	BINOUT( indexCount, UINT );
	for( UINT i = 0; i < inds.size( ); i++ )
	{
		BINOUT( inds[i], UINT );
	}
	//------------------------------------------------------------------------------------------------ Index
	BINOUT( modelInfo, UINT );
	//------------------------------------------------------------------------------------------------ END
	bout.close( );
	return true;
}

bool FbxLoader::Initialize( LPCWSTR inFile, LPCWSTR outFile, bool state )
{
	mIn = std::filesystem::path( inFile );
	mOut = std::filesystem::path( outFile );
	mIsCompressed = state;

	mFbxManager = FbxManager::Create( );
	if( ISERROR2( !mFbxManager, Failed to initialize FBX manager. ) )
		return false;

	FbxIOSettings* ios = FbxIOSettings::Create( mFbxManager, IOSROOT );
	mFbxManager->SetIOSettings( ios );

	FbxString lPath = FbxGetApplicationDirectory( );
	mFbxManager->LoadPluginsDirectory( lPath.Buffer( ) );

	mFbxScene = FbxScene::Create( mFbxManager, "myScene" );
	if( ISERROR2( !mFbxScene, Failed to create FBX scene. ) )
		return false;

	if( ISERROR2( !LoadScene( ), Failed to load scene. ) )
		return false;

	GetContent( );

	return true;
}

bool FbxLoader::LoadScene( )
{
	FbxImporter* lImporter = FbxImporter::Create( mFbxManager, "" );
	if( ISERROR2( !lImporter->Initialize( mIn.string( ).c_str( ), -1, mFbxManager->GetIOSettings( ) ), Failed to load scene. ) )
		return false;

	if( ISERROR2( !lImporter->Import( mFbxScene ), Failed to load scene. ) )
		return false;

	lImporter->Destroy( );

	return true;
}

void FbxLoader::GetContent( )
{
	FbxNode* lNode = mFbxScene->GetRootNode( );

	if( lNode )
	{
		for( int i = 0; i < lNode->GetChildCount( ); i++ )
			GetContent( lNode->GetChild( i ) );
	}
}

void FbxLoader::GetContent( FbxNode * pNode )
{
	FbxNodeAttribute::EType lAttributeType;
	int i;

	if( pNode->GetNodeAttribute( ) == NULL )
		FBXSDK_printf( "NULL Node Attribute\n\n" );
	else
	{
		lAttributeType = ( pNode->GetNodeAttribute( )->GetAttributeType( ) );

		switch( lAttributeType )
		{
			case FbxNodeAttribute::eMesh:
				GetMesh( pNode );
				break;
			default:
				break;
		}
	}

	for( i = 0; i < pNode->GetChildCount( ); i++ )
	{
		GetContent( pNode->GetChild( i ) );
	}
}

void FbxLoader::GetMesh( FbxNode * pNode )
{
	FbxMesh* lMesh = ( FbxMesh* )pNode->GetNodeAttribute( );
	GetPolygons( lMesh );
}

void FbxLoader::Shutdown( )
{
	if( mFbxManager ) mFbxManager->Destroy( );
}
