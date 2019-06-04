#include "Engine.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define IDR_ACCEL1 151

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//	_CrtSetBreakAlloc();

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	return engine->Run();
}