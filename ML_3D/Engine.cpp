#include "Global.h"
#include "Engine.h"

Engine::Engine() noexcept
{}

void Engine::Initialize()
{
	mEditor = std::make_unique<Editor>();
	mEditor->Initialize();

	RECT rc;
	GetClientRect( mEditor->mMainWindow->RenderWnd(), &rc );

#if ISD3DRENDERER
	mRenderer = new RendererD3D;
#else
	mRenderer = new RendererOGL;
#endif // ISD3DRENDERER

	if( !mRenderer->Initialize( mEditor->mMainWindow->RenderWnd(), rc.right - rc.left, rc.bottom - rc.top ) )
		REPORTMSG( Initialize(), 0, Initialize() failed to create mRenderer. );
}

void Engine::Update()
{
	MSG msg = { 0 };
	ZeroMemory( &msg, sizeof( MSG ) );
	PeekMessage( &msg, nullptr, 0u, 0u, PM_NOREMOVE );

	mEditor->mMSG = &msg;

	while( msg.message != WM_QUIT )
	{
#if ISEDITORMODE
		mEditor->Update();
#endif // ISEDITORMODE

		mRenderer->Render();
	}

	mRet = static_cast< int >( msg.wParam );
}

void Engine::Terminate()
{
	mRenderer->Terminate();
	delete mRenderer;
	mEditor->Terminate();
}

int Engine::Run()
{
	Initialize();
	Update();
	Terminate();
	return mRet;
}
