#pragma once
//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define LOG(level, ...)\
{\
	char buffer[1024];\
	sprintf(buffer, __VA_ARGS__);\
	zeus::Logger::Log(zeus::LogLevel::level, __FILE__, __LINE__, __FUNCTION__, buffer, true);\
	puts("");\
	if (zeus::LogLevel::level == zeus::LogLevel::Error) while(true);\
}

#define QUICK_LOG(level, ...)\
{\
	char buffer[1024];\
	sprintf(buffer, __VA_ARGS__);\
	zeus::Logger::Log(zeus::LogLevel::level, __FILE__, __LINE__, __FUNCTION__, buffer, false);\
	puts("");\
}\

#ifdef ZUES_ENGINE
	#define LOG_ENGINE(level, ...)\
	{\
		char buffer[1024];\
		sprintf(buffer, __VA_ARGS__);\
		zeus::Logger::Log(zeus::LogLevel::level, __FILE__, __LINE__, __FUNCTION__, buffer, false, true);\
		puts("");\
	}
#endif

namespace zeus
{
	enum class LogLevel
	{
		Info	= 0,
		Trace	= 1,
		Warn	= 2,
		Error	= 3
	};

	class Logger
	{
	public:
		static void Log(LogLevel level, const char* filename, int line, const char* function, const char* msg, bool showInfo = true, bool engine = false);
	};
}
