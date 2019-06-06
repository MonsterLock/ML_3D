#pragma once
#include "WindowMessengerBase.h"

class WindowMessenger : public WindowMessengerBase< WindowMessenger>
{
public:
	PCWSTR ClassName() const { return L"WindowMessenger"; }
	PCWSTR WindowText() const { return L"Messenger"; }
	LRESULT HandleMessage( UINT, WPARAM, LPARAM );
};

