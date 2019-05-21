#include "Engine.h"



Engine::Engine()
{}


Engine::~Engine()
{}

int Engine::Run()
{
	if ( !win.Create(
		L"ML 3D Engine"
	) )
	{
		MessageBox( nullptr, L"Creating GUI Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
		return 0;
	}

	// Run the message loop.
	MSG msg = {};
	BOOL bRet;

	while ( ( bRet = GetMessage( &msg, static_cast< HWND >( nullptr ), 0, 0 ) ) != 0 )
	{
		if ( bRet == -1 )
		{
			MessageBox( nullptr, L"GetMessage for GUI Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION );
		}
		else
		{
			if ( !TranslateMDISysAccel( win.ClientWnd(), &msg ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
	}

	return msg.wParam;
}

BOOL Engine::Init()
{
	return 0;
}

BOOL Engine::Release()
{
	return 0;
}
