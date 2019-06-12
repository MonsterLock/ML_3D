#include "Global.h"
#include "Engine.h"

Engine::Engine() noexcept
	:
	mIsEditor( false ),
	mIsDirectX( true ),
	mIsRunning( true )
{}

void Engine::Initialize()
{
	mMode = mIsEditor ?
		std::shared_ptr<Mode>( new Editor() ) : std::shared_ptr<Mode>( new Game() );
	mMode->Initialize();

	mRenderer = mIsDirectX ?
		std::shared_ptr<Renderer>( new RendererD3D() ) : std::shared_ptr<Renderer>( new RendererOpenGL() );
	mRenderer->Initialize( mMode->GetRenderWnd() );
}

void Engine::Update()
{
	// TODO: Add switch modes.
	mRet = mMode->Update( mRenderer );
}

void Engine::Terminate()
{
	mRenderer->Terminate();
	mMode->Terminate();
}

int Engine::Run()
{
	Initialize();
	Update();
	Terminate();
	return mRet;
}
