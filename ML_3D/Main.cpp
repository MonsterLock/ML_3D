#include "MainWindow.h"

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow )
{
	MainWindow win;

	if ( !win.Create( L"ML_3D", WS_OVERLAPPEDWINDOW, 0,
					  CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
					  0, 0) )
	{
		return 0;
	}

	ShowWindow( win.Window(), nCmdShow );

	// Run the message loop.
	MSG msg = {};
	while ( GetMessage( &msg, nullptr, 0, 0 ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	return 0;
}
