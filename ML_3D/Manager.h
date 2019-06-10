#pragma once
#include "Global.h"

class Manager
{
public:
	virtual BOOL Initialize() = 0;
	virtual void Update() = 0;
	virtual void Terminate() = 0;
};