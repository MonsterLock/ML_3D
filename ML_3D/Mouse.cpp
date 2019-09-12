#include "Global.h"
#include "Mouse.h"

Mouse::Mouse( ) noexcept
	:
	mPos( { 0, 0 } )
{ }

bool Mouse::Initialize( )
{
	mButtons = 0;
	mPos.x = mPos.y = 0;

	RAWINPUTDEVICE Rid;
	ZeroMemory( &Rid, sizeof( Rid ) );
	Rid.usUsagePage = 0x01;
	Rid.usUsage = 0x02;
	Rid.dwFlags = 0;
	Rid.hwndTarget = nullptr;

	if( ISERROR1( !RegisterRawInputDevices( &Rid, 1, sizeof( Rid ) ) ) )
		return false;

	return true;
}

void Mouse::Update( USHORT state, USHORT key, UINT x, UINT y )
{
	switch( key )
	{
		case RI_MOUSE_LEFT_BUTTON_DOWN:
		{
			BitM::BitOn( mButtons, Left );
		}
		break;
		case RI_MOUSE_LEFT_BUTTON_UP:
		{
			BitM::BitOff( mButtons, Left );
		}
		break;
		case RI_MOUSE_MIDDLE_BUTTON_DOWN:
		{
			BitM::BitOn( mButtons, Middle );
		}
		break;
		case RI_MOUSE_MIDDLE_BUTTON_UP:
		{
			BitM::BitOff( mButtons, Middle );
		}
		break;
		case RI_MOUSE_RIGHT_BUTTON_DOWN:
		{
			BitM::BitOn( mButtons, Right );
		}
		break;
		case RI_MOUSE_RIGHT_BUTTON_UP:
		{
			BitM::BitOff( mButtons, Right );
		}
		break;
		case RI_MOUSE_BUTTON_4_DOWN:
		{
			BitM::BitOn( mButtons, Xtra1 );
		}
		break;
		case RI_MOUSE_BUTTON_4_UP:
		{
			BitM::BitOff( mButtons, Xtra1 );
		}
		break;
		case RI_MOUSE_BUTTON_5_DOWN:
		{
			BitM::BitOn( mButtons, Xtra2 );
		}
		break;
		case RI_MOUSE_BUTTON_5_UP:
		{
			BitM::BitOff( mButtons, Xtra2 );
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

void Mouse::Reset( )
{
	mButtons = 0;
	mPos.x = mPos.y = 0;
}

bool Mouse::CheckState( UINT button )
{
	return BitM::BitIsOn( mButtons, button );
}

void Mouse::SetMousePos( UINT x, UINT y )
{
	mPos.x = x;
	mPos.y = y;
}

POINT Mouse::GetMousePos( )
{
	return mPos;
}
