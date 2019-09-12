#pragma once
#include "Mouse.h"
#include "Keyboard.h"

class Input
{
	Mouse* mMouse;
	Keyboard* mKeyboard;

public:
	Input( ) noexcept;
	bool Initialize( );
	void Update( UINT, WPARAM, LPARAM );
	void Shutdown( );
	bool CheckKeyboardState( UINT );
	bool CheckMouseState( UINT );
	POINT GetMousePos( );
};
