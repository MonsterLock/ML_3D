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
	ErrorHandler( const std::wstring& type, const std::wstring& file, const std::wstring& line, const std::wstring& what )
		:
		type( type ),
		file( file ),
		line( line ),
		what( what )
	{}

	std::wstring GetError()
	{
		return std::wstring(
			L"[TYPE] " + type +
			L"\n[FILE] " + file +
			L"\n[LINE] " + line +
			L"\n\n[ERROR]\n" + what
		);
	}

	void PopUpError()
	{
		MessageBox( nullptr, GetError().c_str(), L"Error Encountered!", MB_OK | MB_ICONWARNING );
	}
};