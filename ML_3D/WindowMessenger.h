#pragma once
#include "WindowMessengerBase.h"
class WindowMessenger : public WindowMessengerBase< WindowMessenger>
{
public:
	WindowMessenger();
	~WindowMessenger();
};

