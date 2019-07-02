#pragma once

#include "Mouse.h"
#include "Keyboard.h"

class Input
{
	std::unique_ptr<Mouse> m_mouse;
	std::unique_ptr<Keyboard> m_keyboard;

public:
	Input() noexcept;

	void Initialize( HWND );
	void Update( UINT uMsg, WPARAM wParam, LPARAM lParam );
	void Shutdown( );
	POINT GetMousePos( );
	bool CheckKeyboard( UINT );
	bool CheckMouse( UINT );
};

