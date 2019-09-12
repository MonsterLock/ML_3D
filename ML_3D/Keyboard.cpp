#include "Global.h"
#include "Keyboard.h"

Keyboard::Keyboard( ) noexcept
{
	ZeroMemory( mKeys, sizeof( mKeys ) );
}

bool Keyboard::Initialize( )
{
	ZeroMemory( mKeys, sizeof( mKeys ) );

	RAWINPUTDEVICE Rid;
	ZeroMemory( &Rid, sizeof( Rid ) );
	Rid.usUsagePage = 0x01;
	Rid.usUsage = 0x06;
	Rid.dwFlags = 0;
	Rid.hwndTarget = nullptr;

	if( ISERROR1( !RegisterRawInputDevices( &Rid, 1, sizeof( Rid ) ) ) )
		return false;

	return true;
}

void Keyboard::Update( USHORT key, BOOL state )
{
	UINT keyIndex = TranslateKey( key );

	if( keyIndex > 0 )
	{
		switch( state )
		{
			case RI_KEY_MAKE:
			{
				BitM::BitSetOn( mKeys, keyIndex );
			}
			break;
			case RI_KEY_BREAK:
			{
				BitM::BitSetOff( mKeys, keyIndex );
			}
			break;
			default:
				break;
		}
		//BitM::PrintBitStream( mKeys, GETARRAYSIZE( mKeys ) );
	}
}

void Keyboard::Reset( )
{
	ZeroMemory( mKeys, sizeof( mKeys ) );
}

bool Keyboard::CheckState( UINT key )
{
	return BitM::BitSetIsOn( mKeys, key );
}

UINT Keyboard::TranslateKey( USHORT key )
{
	switch( key )
	{
		case VK_BACK:
			return 1;
		case VK_TAB:
			return 2;
		case VK_RETURN:
			return 3;
		case VK_PAUSE:
			return 4;
		case VK_CAPITAL:
			return 5;
		case VK_ESCAPE:
			return 6;
		case VK_SPACE:
			return 7;
		case VK_PRIOR:
			return 8;
		case VK_NEXT:
			return 9;
		case VK_END:
			return 10;
		case VK_HOME:
			return 11;
		case VK_LEFT:
			return 12;
		case VK_UP:
			return 13;
		case VK_RIGHT:
			return 14;
		case VK_DOWN:
			return 15;
		case VK_SELECT:
			return 16;
		case VK_PRINT:
			return 17;
		case VK_EXECUTE:
			return 18;
		case VK_SNAPSHOT:
			return 19;
		case VK_INSERT:
			return 20;
		case VK_DELETE:
			return 21;
		case VK_HELP:
			return 22;
		case 0x30:
			return 23;
		case 0x31:
			return 24;
		case 0x32:
			return 25;
		case 0x33:
			return 26;
		case 0x34:
			return 27;
		case 0x35:
			return 28;
		case 0x36:
			return 29;
		case 0x37:
			return 30;
		case 0x38:
			return 31;
		case 0x39:
			return 32;
		case 0x41:
			return 33;
		case 0x42:
			return 34;
		case 0x43:
			return 35;
		case 0x44:
			return 36;
		case 0x45:
			return 37;
		case 0x46:
			return 38;
		case 0x47:
			return 39;
		case 0x48:
			return 40;
		case 0x49:
			return 41;
		case 0x4A:
			return 42;
		case 0x4B:
			return 43;
		case 0x4C:
			return 44;
		case 0x4D:
			return 45;
		case 0x4E:
			return 46;
		case 0x4F:
			return 47;
		case 0x50:
			return 48;
		case 0x51:
			return 49;
		case 0x52:
			return 50;
		case 0x53:
			return 51;
		case 0x54:
			return 52;
		case 0x55:
			return 53;
		case 0x56:
			return 54;
		case 0x57:
			return 55;
		case 0x58:
			return 56;
		case 0x59:
			return 57;
		case 0x5A:
			return 58;
		case VK_NUMPAD0:
			return 59;
		case VK_NUMPAD1:
			return 60;
		case VK_NUMPAD2:
			return 61;
		case VK_NUMPAD3:
			return 62;
		case VK_NUMPAD4:
			return 63;
		case VK_NUMPAD5:
			return 64;
		case VK_NUMPAD6:
			return 65;
		case VK_NUMPAD7:
			return 66;
		case VK_NUMPAD8:
			return 67;
		case VK_NUMPAD9:
			return 68;
		case VK_MULTIPLY:
			return 69;
		case VK_ADD:
			return 70;
		case VK_SEPARATOR:
			return 71;
		case VK_SUBTRACT:
			return 72;
		case VK_DECIMAL:
			return 73;
		case VK_DIVIDE:
			return 74;
		case VK_F1:
			return 75;
		case VK_F2:
			return 76;
		case VK_F3:
			return 77;
		case VK_F4:
			return 78;
		case VK_F5:
			return 79;
		case VK_F6:
			return 80;
		case VK_F7:
			return 81;
		case VK_F8:
			return 82;
		case VK_F9:
			return 83;
		case VK_F10:
			return 84;
		case VK_F11:
			return 85;
		case VK_F12:
			return 86;
		case VK_F13:
			return 87;
		case VK_F14:
			return 88;
		case VK_F15:
			return 89;
		case VK_F16:
			return 90;
		case VK_F17:
			return 91;
		case VK_F18:
			return 92;
		case VK_F19:
			return 93;
		case VK_F20:
			return 94;
		case VK_F21:
			return 95;
		case VK_F22:
			return 96;
		case VK_F23:
			return 97;
		case VK_F24:
			return 98;
		case VK_SCROLL:
			return 99;
		case VK_LSHIFT:
			return 100;
		case VK_RSHIFT:
			return 101;
		case VK_LCONTROL:
			return 102;
		case VK_RCONTROL:
			return 103;
		case VK_LMENU:
			return 104;
		case VK_RMENU:
			return 105;
		case VK_BROWSER_BACK:
			return 106;
		case VK_BROWSER_FORWARD:
			return 107;
		case VK_BROWSER_REFRESH:
			return 108;
		case VK_BROWSER_STOP:
			return 109;
		case VK_BROWSER_SEARCH:
			return 110;
		case VK_BROWSER_FAVORITES:
			return 111;
		case VK_BROWSER_HOME:
			return 112;
		case VK_VOLUME_MUTE:
			return 113;
		case VK_VOLUME_DOWN:
			return 114;
		case VK_VOLUME_UP:
			return 115;
		case VK_MEDIA_NEXT_TRACK:
			return 116;
		case VK_MEDIA_PREV_TRACK:
			return 117;
		case VK_MEDIA_STOP:
			return 118;
		case VK_MEDIA_PLAY_PAUSE:
			return 119;
		case VK_OEM_1:
			return 120;
		case VK_OEM_PLUS:
			return 121;
		case VK_OEM_COMMA:
			return 122;
		case VK_OEM_MINUS:
			return 123;
		case VK_OEM_PERIOD:
			return 124;
		case VK_OEM_2:
			return 125;
		case VK_OEM_3:
			return 126;
		case VK_OEM_4:
			return 127;
		case VK_OEM_5:
			return 128;
		case VK_OEM_6:
			return 129;
		case VK_OEM_7:
			return 130;
		case VK_OEM_102:
			return 131;
		case VK_ATTN:
			return 132;
		case VK_CRSEL:
			return 133;
		case VK_EXSEL:
			return 134;
		case VK_EREOF:
			return 135;
		case VK_PLAY:
			return 136;
		case VK_ZOOM:
			return 137;
		case VK_OEM_CLEAR:
			return 138;
		default:
			return 0;
	}
}

