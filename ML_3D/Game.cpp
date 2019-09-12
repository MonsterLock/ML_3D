#include "Global.h"
#include "Game.h"

StepTimer stepTimer;

void Game::Initialize()
{
	mWindowMain = std::shared_ptr<WindowMain>( new WindowMain );
	mWindowMain->Create();

	mRenderWindow = mWindowMain->Wnd();

	mRenderEngine = std::make_unique<RenderEngine>();
	mRenderEngine->Initialize( mWindowMain->Wnd() );
}

void Game::Update()
{
	MSG msg = { 0 };
	ZeroMemory( &msg, sizeof( MSG ) );
	PeekMessage( &msg, nullptr, 0u, 0u, PM_NOREMOVE );

	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
		{
#if ISWMMSGSHOW
			OutputDebugString( ConvertMessage( msg ).c_str() );
#endif
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			stepTimer.Tick();
			if( stepTimer.GetFrameCount() > 0 )
				mRenderEngine->Frame();
		}
	}

	mMsg = static_cast< int >( msg.wParam );
}

void Game::Shutdown()
{
	mRenderEngine->Shutdown( );
}
