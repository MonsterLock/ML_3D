#include "Global.h"
#include "Input.h"

Input::Input( ) noexcept
	:
	mMouse( nullptr ),
	mKeyboard( nullptr )
{ }

bool Input::Initialize( )
{
	mMouse = new Mouse;
	if( !mMouse->Initialize( ) )
		return false;

	mKeyboard = new Keyboard;
	if( !mKeyboard->Initialize( ) )
		return false;

	return true;
}

void Input::Update( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	UINT dwSize;

	GetRawInputData( reinterpret_cast< HRAWINPUT >( lParam ), RID_INPUT, nullptr, &dwSize, sizeof( RAWINPUTHEADER ) );

	LPBYTE lpb = new BYTE[dwSize];

	if( !lpb ) return;

	if( GetRawInputData( reinterpret_cast< HRAWINPUT >( lParam ), RID_INPUT, lpb, &dwSize, sizeof( RAWINPUTHEADER ) ) != dwSize )
		OutputDebugString( TEXT( "GetRawInputData does not return correct size !\n" ) );

	RAWINPUT* raw = reinterpret_cast< RAWINPUT* >( lpb );

	if( raw->header.dwType == RIM_TYPEKEYBOARD )
		mKeyboard->Update( raw->data.keyboard.VKey, raw->data.keyboard.Flags );
	else if( raw->header.dwType == RIM_TYPEMOUSE )
		mMouse->Update( raw->data.mouse.usFlags, raw->data.mouse.usButtonFlags, raw->data.mouse.lLastX, raw->data.mouse.lLastY );

	delete[] lpb;
}

void Input::Shutdown( )
{
	if( mMouse )
	{
		delete mMouse;
		mMouse = nullptr;
	}

	if( mKeyboard )
	{
		delete mKeyboard;
		mKeyboard = nullptr;
	}
}

bool Input::CheckKeyboardState( UINT key )
{
	return mKeyboard->CheckState( key );
}

bool Input::CheckMouseState( UINT button )
{
	return mMouse->CheckState( button );
}

POINT Input::GetMousePos( )
{
	return mMouse->GetMousePos( );
}