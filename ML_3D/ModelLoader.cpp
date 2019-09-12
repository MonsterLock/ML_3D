#include "Global.h"
#include "ModelLoader.h"
#include "FbxLoader.h"


bool LoadFbx( LPCWSTR inFile, LPCWSTR outFile, bool state )
{
	FbxLoader converter;

	if( ISERROR2( !converter.Initialize( inFile, outFile, state ), Failed to create convert FBX. ) ) return false;

	converter.Shutdown( );

	return true;
}
