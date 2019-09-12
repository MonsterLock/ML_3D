#include "Global.h"
#include "App.h"

int APIENTRY wWinMain( HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow )
{
	#if NDEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	// _CrtSetBreakAlloc();
	#endif

	App* app = new App;
	app->Initialize( 1 );
	app->Update( );
	app->Shutdown( );

	return 0;
}