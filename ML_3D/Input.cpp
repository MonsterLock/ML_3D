#include "Global.h"
#include "Input.h"


Input::Input() noexcept
{}

Input::Input( const Input & ) noexcept
{}

Input::~Input()
{}

void Input::Initialize()
{
	ZeroMemory( &mKeys, sizeof( bool ) * 256 );
}

void Input::KeyDown( UINT index )
{
	mKeys[index] = true;
}

void Input::KeyUp( UINT index )
{
	mKeys[index] = true;
}

bool Input::IsKeyDown( UINT index)
{
	return false;
}
