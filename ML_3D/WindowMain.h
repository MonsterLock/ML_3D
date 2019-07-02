#pragma once
#include "WindowBase.h"
#include "Input.h"

class WindowMain : public WindowBase<WindowMain>
{

public:
	WindowMain( ) noexcept;
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
	std::shared_ptr<Input> m_input;
};
