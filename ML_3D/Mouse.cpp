#include "Global.h"
#include "Mouse.h"

Mouse::Mouse( ) noexcept
	:
	m_pos( { 0, 0 } )
{ }

void Mouse::Initialize( HWND hwnd )
{
	RAWINPUTDEVICE Rid;

	Rid.usUsagePage = 0x01;
	Rid.usUsage = 0x02;
	Rid.dwFlags = 0;
	Rid.hwndTarget = hwnd;

	TESTRESULT( !RegisterRawInputDevices( &Rid, 1, sizeof( Rid ) ) );
}

void Mouse::Update( USHORT state, USHORT key, UINT x, UINT y )
{
	switch( key )
	{
		case RI_MOUSE_LEFT_BUTTON_DOWN:
		{
			BITON( m_mouse, MouseInput::Left );
		}
		break;
		case RI_MOUSE_LEFT_BUTTON_UP:
		{
			BITOFF( m_mouse, MouseInput::Left );
		}
		break;
		case RI_MOUSE_MIDDLE_BUTTON_DOWN:
		{
			BITON( m_mouse, MouseInput::Middle );
		}
		break;
		case RI_MOUSE_MIDDLE_BUTTON_UP:
		{
			BITOFF( m_mouse, MouseInput::Middle );
		}
		break;
		case RI_MOUSE_RIGHT_BUTTON_DOWN:
		{
			BITON( m_mouse, MouseInput::Right );
		}
		break;
		case RI_MOUSE_RIGHT_BUTTON_UP:
		{
			BITOFF( m_mouse, MouseInput::Right );
		}
		break;
		case RI_MOUSE_BUTTON_4_DOWN:
		{
			BITON( m_mouse, MouseInput::Xtra1 );
		}
		break;
		case RI_MOUSE_BUTTON_4_UP:
		{
			BITOFF( m_mouse, MouseInput::Xtra1 );
		}
		break;
		case RI_MOUSE_BUTTON_5_DOWN:
		{
			BITON( m_mouse, MouseInput::Xtra2 );
		}
		break;
		case RI_MOUSE_BUTTON_5_UP:
		{
			BITOFF( m_mouse, MouseInput::Xtra2 );
		}
		break;
		case RI_MOUSE_WHEEL:
		{

		}
		break;
		default:
			break;
	}
	SetMousePos( x, y );
}

bool Mouse::CheckState( UINT index )
{
	return BITTEST( m_mouse, index );
}

void Mouse::SetMousePos( UINT x, UINT y )
{
	m_pos.x = x;
	m_pos.y = y;
}

POINT Mouse::GetMousePos( )
{
	return m_pos;
}
