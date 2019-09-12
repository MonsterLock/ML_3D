#pragma once
#include "Global.h"

#define ISERROR1(condition) ml3d::IsError( condition, L#condition, __FILE__, __LINE__ )
#define ISERROR2(condition, type) ml3d::IsError( condition, L#condition, L#type, __FILE__, __LINE__ )

namespace ml3d
{
	static std::wstring PrintError( LPCTSTR conditionToString, LPCSTR file, int line )
	{
		LPVOID lpMsgBuf;
		DWORD dw = GetLastError( );
		std::filesystem::path path = std::filesystem::path( file );

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			dw,
			MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
			reinterpret_cast< LPTSTR >( &lpMsgBuf ),
			0,
			nullptr );

		std::wstringstream oss;
		oss
			<< L"Error Code " << dw << L"(0x" << std::hex << dw << L"),\n" << reinterpret_cast< LPCTSTR >( lpMsgBuf )
			<< std::dec << std::endl
			<< L"Line " << line << L",\n" << path.filename( ) << std::endl << std::endl
			<< conditionToString << std::endl;

		LocalFree( lpMsgBuf );

		return oss.str( );
	}

	static std::wstring PrintError( LPCTSTR conditionToString, LPCTSTR type, LPCSTR file, int line )
	{
		std::wstringstream oss;
		std::filesystem::path path = std::filesystem::path( file );

		oss
			<< L"Error Type:\n" << type << std::endl << std::endl
			<< L"Line " << line << L",\n" << path.filename( ) << std::endl << std::endl
			<< conditionToString << std::endl;

		return oss.str( );
	}

	static bool IsError( BOOL condition, LPCTSTR conditionToString, LPCSTR file, int line )
	{
		if( condition )
		{
			MessageBox( NULL, PrintError( conditionToString, file, line ).c_str( ), L"Error1", MB_OK | MB_ICONERROR );

			return true;
		}

		return false;
	}

	static bool IsError( BOOL condition, LPCTSTR conditionToString, LPCWSTR type, LPCSTR file, int line )
	{
		if( condition )
		{
			MessageBox( NULL, PrintError( conditionToString, type, file, line ).c_str( ), L"Error1", MB_OK | MB_ICONERROR );

			return true;
		}

		return false;
	}
}