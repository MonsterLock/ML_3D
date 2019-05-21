#pragma once
#include <string>

template <class T>
class IElement
{
	std::wstring identity;
	T component;

public:
	Element( const std::wstring& identity ) : identity( identity ) {}
	const wchar* GetIdentity() const noexcept
	{
		return identity;
	}
	virtual ~Element() = 0;
};