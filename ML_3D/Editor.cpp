#include "Global.h"
#include "Editor.h"

Editor::Editor() noexcept
	:
	mHAccel( nullptr ),
	mMSG( nullptr )
{}

BOOL Editor::Initialize()
{
	InitCommonControls();

	mMainWindow = std::make_unique<MainWindow>();
	if( !mMainWindow->Create() )
	{
		REPORTMSG( Create(), 0, Create() failed to create mMainWindow. );
		return FALSE;
	}

	mHAccel = LoadAccelerators( GetModuleHandle( nullptr ), MAKEINTRESOURCE( IDR_ACCEL1 ) );
	if( !mHAccel )
	{
		REPORTMSG( LoadAccelerators(), nullptr, LoadAccelerators() failed to assign mHAccel a valid HACCEL. );
		return FALSE;
	}

	return TRUE;
}

void Editor::Update()
{
	if( PeekMessage( mMSG, nullptr, 0, 0, PM_REMOVE )
		   && !TranslateMDISysAccel( mMainWindow->ClientWnd(), mMSG )
		   && !TranslateAccelerator( mMainWindow->FrameWnd(), mHAccel, mMSG ) )
	{
#if ISWMMSGSHOW
		OutputDebugString( ConvertMessage( msg ).c_str() );
#endif
		TranslateMessage( mMSG );
		DispatchMessage( mMSG );
	}
}

void Editor::Terminate()
{
	if( mMSG )
		mMSG = nullptr;
}
