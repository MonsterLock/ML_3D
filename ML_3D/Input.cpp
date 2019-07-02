#include "Global.h"
#include "Input.h"

Input::Input( ) noexcept
{ }

void Input::Initialize( HWND hwnd )
{
	m_mouse = std::make_unique<Mouse>( );
	m_mouse->Initialize( nullptr );
	m_keyboard = std::make_unique<Keyboard>( );
	m_keyboard->Initialize( nullptr );
}

void Input::Update( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	UINT dwSize;

	GetRawInputData( reinterpret_cast< HRAWINPUT >( lParam ), RID_INPUT, nullptr, &dwSize,
					 sizeof( RAWINPUTHEADER ) );

	LPBYTE lpb = new BYTE[dwSize];

	if( !lpb )
		return;

	if( GetRawInputData( reinterpret_cast< HRAWINPUT >( lParam ), RID_INPUT, lpb, &dwSize, sizeof( RAWINPUTHEADER ) ) != dwSize )
		OutputDebugString( TEXT( "GetRawInputData does not return correct size !\n" ) );

	RAWINPUT* raw = reinterpret_cast< RAWINPUT* >( lpb );

	if( raw->header.dwType == RIM_TYPEKEYBOARD )
	{
		m_keyboard->Update( raw->data.keyboard.VKey, raw->data.keyboard.Flags );
	}
	else if( raw->header.dwType == RIM_TYPEMOUSE )
	{
		m_mouse->Update( raw->data.mouse.usFlags, raw->data.mouse.usButtonFlags, raw->data.mouse.lLastX, raw->data.mouse.lLastY );
	}

	delete[] lpb;
}

POINT Input::GetMousePos( )
{
	return m_mouse->GetMousePos( );
}

bool Input::CheckKeyboard( UINT key )
{
	return m_keyboard->CheckState( key );
}

bool Input::CheckMouse( UINT key )
{
	return m_mouse->CheckState( key );
}

