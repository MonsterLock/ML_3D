#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>

namespace ml3d
{
	namespace CORE
	{
		static std::string GetError( const char* t_blame , const char* t_file , int t_line )
		{
			void* lpMsgBuf;
			unsigned long dw = GetLastError( );

			FormatMessageA(
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS ,
				nullptr , dw ,
				MAKELANGID( LANG_NEUTRAL , SUBLANG_DEFAULT ) ,
				reinterpret_cast< LPSTR >( &lpMsgBuf ) ,
				0 , nullptr );

			std::stringstream oss;
			oss << __DATE__ << ", " << __TIME__ << std::endl
				<< "[Blame] " << t_blame << std::endl
				<< "[Line " << t_line << "] " << t_file << std::endl
				<< "[Code 0x" << std::hex << dw << std::dec << "] " << reinterpret_cast< LPSTR >( lpMsgBuf );
			LocalFree( lpMsgBuf );

			return oss.str( );
		}

		static std::string SetError( const char* t_blame , int t_error , const char* t_file , int t_line )
		{
			std::stringstream oss;
			oss << __DATE__ << ", " << __TIME__ << std::endl
				<< "[Blame] " << t_blame << std::endl
				<< "[Line " << t_line << "] " << t_file << std::endl
				<< "[Code] " << t_error;

			return oss.str( );
		}

		static std::string SetError( const char* t_blame , int t_error , const char* t_notes, const char* t_file , int t_line )
		{
			std::stringstream oss;
			oss << __DATE__ << ", " << __TIME__ << std::endl
				<< "[Blame] " << t_blame << std::endl
				<< "[Line " << t_line << "] " << t_file << std::endl
				<< "[Code] " << t_error << std::endl
				<< "[Notes] " << t_notes;

			return oss.str( );
		}

		static void LogFile( const char* t_filename , const std::string log )
		{
			OutputDebugStringA( "\nLogged Error.\n" );
			std::ofstream fout( t_filename , std::ios::app );
			fout << log;
			fout.close( );
		}
	} // namespace error
} // namespace ml3d