#include "Global.h"
#include "Game.h"

extern StepTimer stepTimer;

void Game::Initialize()
{
	mWindowMain = std::make_unique<WindowMain>();
	if( !mWindowMain->Create() )
		REPORTMSG( Create(), 0, Create() failed to create mWindowMain. );

	mRender = mWindowMain->Wnd();
}

int Game::Update( std::shared_ptr<Renderer> renderer )
{
	MSG msg = { 0 };
	ZeroMemory( &msg, sizeof( MSG ) );
	PeekMessage( &msg, nullptr, 0u, 0u, PM_NOREMOVE );

	while( msg.message != WM_QUIT )
	{
		mIsMsgReceived = PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE );

		if( IsMsgReceived() )
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
			renderer->Render();
		}
	}

	return static_cast< int >( msg.wParam );
}

void Game::Terminate()
{ return; }
