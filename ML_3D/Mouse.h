#pragma once
#include "Global.h"

class Mouse
{
	UINT mButtons;
	POINT mPos;

public:
	Mouse( ) noexcept;
	bool Initialize( );
	void Update( USHORT state, USHORT key, UINT x, UINT y );
	void Reset( );
	bool CheckState( UINT button );
	void SetMousePos( UINT x, UINT y );
	POINT GetMousePos( );

	enum Buttons
	{
		Left,
		Middle,
		Right,
		Xtra1,
		Xtra2,
		Wheel,
		numMouseButtons
	};
};