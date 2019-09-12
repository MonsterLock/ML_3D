#include "Global.h"
#include "App.h"

App::App( ) noexcept
	:
	mEditor( nullptr ),
	mGame( nullptr )
{ }

void App::Initialize( UINT state )
{
	switch( state )
	{
		case 0:
		{
			mEditor = new Editor;
			mEditor->Initialize( );
		}
		break;
		case 1:
		{
			mGame = new Game;
			mGame->Initialize( );
		}
		break;
		default:
			break;
	}
}

void App::Update( )
{
	if( mEditor )
	{
		mEditor->Update( );
	}
	else if( mGame )
	{
		mGame->Update( );
	}
}

void App::Shutdown( )
{
	if( mEditor )
	{
		mEditor->Shutdown( );
		delete mEditor;
		mEditor = nullptr;
	}
	if( mGame )
	{
		mGame->Shutdown( );
		delete mGame;
		mGame = nullptr;
	}
}