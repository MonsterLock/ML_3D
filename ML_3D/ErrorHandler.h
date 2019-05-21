#pragma once
#include <windows.h>
#include <exception>
#include <string>

class ErrorHandler : public std::exception
{
	std::wstring
		type,
		file,
		line,
		what;

public:
	ErrorHandler( const std::wstring& type, const std::wstring& file, const std::wstring& what, const std::wstring& line )
		:
		type( type ),
		what( what ),
		file( file ),
		line( line )
	{}

	std::wstring GetError()
	{
		return std::wstring(
			L"[TYPE] " + type +
			L"\n[FILE] " + file +
			L"\n[LINE] " + line +
			L"\n\n[ERROR] " + what
		);
	}

	void PopUpError()
	{
		MessageBox( nullptr, GetError().c_str(), L"Error Encountered!", MB_OK | MB_ICONWARNING );
	}
};