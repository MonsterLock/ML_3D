#pragma once
#include "Global.h"

template <class T>
class IElement
{
	char id[4];
	T component;

public:
	//Element( const std::wstring& identity ) : identity( identity ) {}
	//const wchar* GetIdentity() const noexcept
	//{
	//	return identity;
	//}
	virtual ~Element() = 0;
};