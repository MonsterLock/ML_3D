#pragma once
#include <windows.h>
#include <string>
#include <sstream>

#define _L(x)  __L(x)
#define __L(x)  L##x
#define MSGLOG(title, what) OutputDebugString( CatchError( L#title, L#what, __FILE__, __LINE__ ).c_str() )

static std::wstring CatchError( LPCWSTR title, LPCWSTR what, LPCSTR file, int line )
{
	std::wstringstream oss;

	oss
		<< L"'" << title << L"': Error '" << file << L"', Line '" << line << "'. " << what << std::endl;

	return oss.str();
}
