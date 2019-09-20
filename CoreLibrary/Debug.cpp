#include "Debug.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <iomanip>

const std::string ML::DEBUG::GetError( const int t_debug_level , const int t_ID , const char *t_caller_name ,
										 const char *t_file_name , const int t_line_number , const char *t_date ,
										 const char *t_time )
{
	std::stringstream oss;
	oss
		<< "________________________________________________________________" << std::endl
		<< "ID: " << t_ID << " Date/Time: " << t_date << ", " << t_time << std::endl
		<< "Level: " << t_debug_level << std::endl
		<< "Caller: " << t_caller_name << std::endl
		<< "Line " << t_line_number << ", " << t_file_name << std::endl;

	return oss.str( );
}

const std::string ML::DEBUG::GetErrorOS( const int t_debug_level , const int t_ID , const char *t_caller_name ,
										   const char *t_file_name , const int t_line_number , const char *t_date ,
										   const char *t_time )
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
	oss
		<< "________________________________________________________________" << std::endl
		<< "ID: " << t_ID << " Date/Time: " << t_date << ", " << t_time << std::endl
		<< "Level: " << t_debug_level << std::endl
		<< "Caller: " << t_caller_name << std::endl
		<< "Line " << t_line_number << ", " << t_file_name << std::endl
		<< "[Code] 0x" << std::hex << dw << std::dec << " [Error] " << reinterpret_cast< LPSTR >( lpMsgBuf ) << std::endl;
	LocalFree( lpMsgBuf );

	return oss.str( );
}

void ML::DEBUG::LogError( const char *t_log_file , const std::string t_error )
{
	OutputDebugStringA( "\nLogged Error.\n" );
	std::ofstream fout( t_log_file , std::ios::app );
	fout << t_error;
	fout.close( );
}

void ML::DEBUG::Output( size_t t_depth , const std::string t_output_string )
{
	std::stringstream oss;
	oss << std::setw( t_depth * 4 ) << "" << t_output_string << std::endl;
	OutputDebugStringA( oss.str( ).c_str( ) );
}
