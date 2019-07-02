#pragma once

namespace MouseInput
{
	enum MouseButtons
	{
		Left,
		Middle,
		Right,
		Xtra1,
		Xtra2,
		Wheel,
		numMouseButtons
	};
}
class Mouse
{
	UINT m_mouse;
	POINT m_pos;

public:
	Mouse( ) noexcept;
	void Initialize( HWND hwnd );
	void Update( USHORT, USHORT, UINT, UINT );
	void Shutdown( );
	bool CheckState( UINT );
	void SetMousePos( UINT, UINT );
	POINT GetMousePos( );
};

