#include "Global.h"
#include "Editor.h"

Editor::Editor() noexcept : mHAccel( nullptr ){}

void Editor::Initialize()
{
	InitCommonControls();

	mHAccel = LoadAccelerators( GetModuleHandle( nullptr ), MAKEINTRESOURCE( IDR_ACCEL1 ) );
	TESTRESULT( !mHAccel );

	mWindowEditor = std::shared_ptr<WindowEditor>( new WindowEditor() );
	mWindowEditor->Create();
	mRenderWindow = mWindowEditor->RenderWnd();

	mRenderEngine = std::make_unique<RenderEngine>();
	mRenderEngine->Initialize( mWindowEditor->RenderWnd() );

	mInput = std::make_unique<Input>();
	mInput->Initialize();
}

void Editor::Update()
{
	MSG msg = { 0 };
	ZeroMemory( &msg, sizeof( MSG ) );
	PeekMessage( &msg, nullptr, 0u, 0u, PM_NOREMOVE );

	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE )
			&& !TranslateMDISysAccel( mWindowEditor->ClientWnd(), &msg )
			&& !TranslateAccelerator( mWindowEditor->FrameWnd(), mHAccel, &msg ) )
		{
#if ISWMMSGSHOW
			OutputDebugString( ConvertMessage( msg ).c_str() );
#endif
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
			mRenderEngine->Render();
	}

	mMsg = static_cast<int>(msg.wParam);
}

void Editor::Terminate()
{
	if( mHAccel ) mHAccel = nullptr;
}
