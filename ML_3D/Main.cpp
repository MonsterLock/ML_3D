#include "MainWindow.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <fbxsdk.h>
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//	_CrtSetBreakAlloc();

	MainWindow win;

	if ( !win.Create(
		L"ML_3D",
		L"ML 3D Engine", MAKEINTRESOURCE( IDR_MAIN_MENU ),
		WS_OVERLAPPEDWINDOW ) )
	{
		return 0;
	}

	ShowWindow( win.Window(), nCmdShow );

	// Run the message loop.
	MSG msg = {};
	BOOL bRet;

	while ( ( bRet = GetMessage( &msg, static_cast< HWND >( nullptr ), 0, 0 ) ) != 0 )
	{
		if ( bRet == -1 )
		{
			// TODO handle the error and possibly exit
		}
		else
		{
			if ( !TranslateMDISysAccel( win.MDIWnd(), &msg ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
	}

	return 0;
}
