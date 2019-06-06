#include "Global.h"
#include "Engine.h"

Engine::Engine() noexcept
	:
	mHAccel( nullptr )
{}

void Engine::Initialize()
{
	InitCommonControls();

	mMainWindow = std::make_unique<MainWindow>();
	if( !mMainWindow->Create() )
		REPORTMSG( Create(), 0, Create() failed to create mMainWindow. );

	RECT rc;
	GetClientRect( mMainWindow->RenderWnd(), &rc );

#if ISD3DRENDERER
	mRenderer = new RendererD3D;
#else
	mRenderer = new RendererOGL;
#endif

	if( !mRenderer->Inititalize( mMainWindow->RenderWnd(), rc.right - rc.left, rc.bottom - rc.top ) )
		REPORTMSG( Inititalize(), 0, Inititalize() failed to create mRenderer. );

	mHAccel = LoadAccelerators( GetModuleHandle( nullptr ), MAKEINTRESOURCE( IDR_ACCEL1 ) );
	if( !mHAccel )
		REPORTMSG( LoadAccelerators(), nullptr, LoadAccelerators() failed to assign mHAccel a valid HACCEL. );
}

void Engine::Update()
{
	bool isMsgObtained;

	MSG msg = {};
	ZeroMemory( &msg, sizeof( MSG ) );

	PeekMessage( &msg, nullptr, 0u, 0u, PM_NOREMOVE );

	while( msg.message != WM_QUIT )
	{
		isMsgObtained = PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE )
			&& !TranslateMDISysAccel( mMainWindow->ClientWnd(), &msg )
			&& !TranslateAccelerator( mMainWindow->FrameWnd(), mHAccel, &msg );

		if( isMsgObtained )
		{
			//OutputDebugString( ConvertMessage( msg ).c_str() );
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		mRenderer->Render();
	}

	mRet = static_cast< int >( msg.wParam );
}

void Engine::Terminate()
{
	mRenderer->Terminate();
	delete mRenderer;
}

int Engine::Run()
{
	Initialize();
	Update();
	Terminate();
	return mRet;
}
