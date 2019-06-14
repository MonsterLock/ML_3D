#include "Global.h"
#include "Engine.h"

Engine::Engine() noexcept
	:
	mIsEditor( 0 ),
	mIsRunning( 1 )
{}

void Engine::Initialize()
{
	mApp = mIsEditor ?
		std::shared_ptr<AppMode>( new Editor() ) : std::shared_ptr<AppMode>( new Game() );
	mApp->Initialize();
}

void Engine::Update()
{
	// TODO: Add switch modes.
	mApp->Update();
}

void Engine::Terminate()
{
	mApp->Terminate();
}

int Engine::Run()
{
	Initialize();
	Update();
	int ret = mApp->GetMsg();
	Terminate();
	return ret;
}
