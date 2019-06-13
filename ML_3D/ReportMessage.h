#pragma once
#include "Global.h"

#define REPORTMSG(title, type, what) OutputDebugString( ReportMessage( L#title, L#type, L#what, __FILE__, __LINE__ ).c_str() )
#define TESTRESULT(condition) TestResult( condition, L#condition, __FILE__, __LINE__ )

static std::wstring ReportMessage( LPCWSTR title, LPCWSTR type, LPCWSTR what, LPCSTR file, int line )
{
	std::wstringstream oss;

	oss
		<< L"'" << title << L"': " << type << L" '" << file << L"', Line '" << line << "'. " << what << std::endl;

	return oss.str();
}

static void TestResult( BOOL condition, LPCWSTR title, LPCSTR file, int line )
{
	if( condition )
	{
		LPVOID lpMsgBuf;
		DWORD dw = GetLastError();

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			dw,
			MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
			( LPTSTR )&lpMsgBuf,
			0, nullptr );

		std::wstringstream oss;

		oss
			<< L"Error Code " << dw << L"(0x" << std::hex << dw << L"),\n" << reinterpret_cast< LPCTSTR >( lpMsgBuf )
			<< std::dec << std::endl
			<< L"Line " << line << L",\n" << file << std::endl << std::endl
			<< title << std::endl;

		LocalFree( lpMsgBuf );
		MessageBox( NULL, oss.str().c_str(), L"Error", MB_OK | MB_ICONERROR );
	}
}