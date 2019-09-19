#pragma once
#include <string>

#ifdef _DEBUG
#define DEBUG_LOG_ERROR( file , level ) ML::DEBUG::LogError( file, ML::DEBUG::GetError( level, __COUNTER__, __FUNCTION__, __FILE__, __LINE__, __DATE__, __TIME__  ) )
#define DEBUG_LOG_ERROR_OS( file , level ) ML::DEBUG::LogError( file, ML::DEBUG::GetErrorOS( level, __COUNTER__, __FUNCTION__, __FILE__, __LINE__, __DATE__, __TIME__  ) )
#define DEBUG_OUTPUT_ERROR( depth , level ) ML::DEBUG::Output( depth, ML::DEBUG::GetError( level, __COUNTER__, __FUNCTION__, __FILE__, __LINE__, __DATE__, __TIME__  ) )
#define DEBUG_OUTPUT( depth , ouput ) ML::DEBUG::Output( depth, output )
#else
#define DEBUG_LOG_ERROR( file , level )
#define DEBUG_LOG_ERROR_OS( file , level )
#define DEBUG_OUTPUT_ERROR( depth , level )
#define DEBUG_OUTPUT( depth , ouput )
#endif

namespace ML
{
	namespace DEBUG
	{
		struct Level
		{
			enum
			{
				NONE = 0 ,
				DEBUG ,
				WARNING ,
				ERROR ,
				FATAL
			};
		};

		struct LogItem
		{
			enum
			{
				DEBUG_LEVEL = 0 ,
				LOG_FILE = 1 ,
				LOG_NAME = 2 ,
				DATE_TIME = 4 ,
				CALLER_NAME = 8 ,
				FILE_NAME = 16 ,
				LINE_NUMBER = 32 ,
				THREAD_ID = 64
			};
		};

		extern const std::string GetError( const int , const int , const char* , const char* , const int , const char* , const char* );

		extern const std::string GetErrorOS( const int , const int , const char* , const char* , const int , const char* , const char* );

		extern void LogError( const char* , const std::string );

		extern void Output( int , const std::string );
	}
}