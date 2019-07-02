#include "Global.h"
#include "Engine.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int APIENTRY wWinMain( HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	// _CrtSetBreakAlloc();

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	return engine->Run( );

	//UINT temp[] = { 1, 2, 3, 4, 5 };
	//OutputDebugString( L"\n" );
	//ToBit( temp, GETARRAYSIZE(temp) );
	//OutputDebugString( L"\n" );
	//BitSetOn( temp, 5 );
	//BitSetOn( temp, 35 );
	//ToBit( temp, GETARRAYSIZE(temp) );
	//if( BitCheck(temp, 35) )
	//{
	//	OutputDebugString( L"TRUE" );
	//}
	//return 0;
}