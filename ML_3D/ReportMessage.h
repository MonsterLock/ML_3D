#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <sstream>

#define REPORTMSG(title, type, what) OutputDebugString( ReportMessage( L#title, L#type, L#what, __FILE__, __LINE__ ).c_str() )

static std::wstring ReportMessage( LPCWSTR title, LPCWSTR type, LPCWSTR what, LPCSTR file, int line )
{
	std::wstringstream oss;

	oss
		<< L"'" << title << L"': " << type << L" '" << file << L"', Line '" << line << "'. " << what << std::endl;

	return oss.str();
}