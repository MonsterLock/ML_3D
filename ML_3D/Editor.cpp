#include "Global.h"
#include "Editor.h"

Editor::Editor() noexcept
	:
	mHAccel( nullptr )
{}

void Editor::Initialize()
{
	InitCommonControls();

	mWindowEditor = std::make_unique<WindowEditor>();
	if( !mWindowEditor->Create() )
		REPORTMSG( Create(), 0, Create() failed to create mWindowEditor. );

	mHAccel = LoadAccelerators( GetModuleHandle( nullptr ), MAKEINTRESOURCE( IDR_ACCEL1 ) );
	if( !mHAccel )
		REPORTMSG( LoadAccelerators(), nullptr, LoadAccelerators() failed to assign mHAccel a valid HACCEL. );

	mRender = mWindowEditor->RenderWnd();
}

int Editor::Update( std::shared_ptr<Renderer> renderer )
{
	MSG msg = { 0 };
	ZeroMemory( &msg, sizeof( MSG ) );
	PeekMessage( &msg, nullptr, 0u, 0u, PM_NOREMOVE );

	while( msg.message != WM_QUIT )
	{
		mIsMsgReceived = PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE )
			&& !TranslateMDISysAccel( mWindowEditor->ClientWnd(), &msg )
			&& !TranslateAccelerator( mWindowEditor->FrameWnd(), mHAccel, &msg );

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
			renderer->Render();
		}
	}

	return static_cast<int>(msg.wParam);
}

void Editor::Terminate()
{
	if( mHAccel ) mHAccel = nullptr;
}
