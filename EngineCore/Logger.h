#pragma once

#include "LibHeader.h"

#include <iostream>
#include "Utils.h"

class Log
{
public:

	static ENGINECORE_API void Info		(const char* msg);
	static ENGINECORE_API void Error	(const char* msg);

	static ENGINECORE_API void Info		(const std::string & msg);
	static ENGINECORE_API void Error	(const std::string & msg);

	/*template<typename ... Args>
	static ENGINECORE_API void Info		(const std::string& format, Args&& ... args);

	template<typename ... Args>
	static ENGINECORE_API void Error	(const std::string& format, Args&& ... args);*/


private:
	Log();

};


//
//#ifdef ENGINE_CORE_EXPORTS
//
//template <typename ... Args>
//void Log::Info(const std::string& format, Args&&... args)
//{
//	Log::Info(string_format(format, args...));
//}
//
//template <typename ... Args>
//void Log::Error(const std::string& format, Args&&... args)
//{
//	Log::Error(string_format(format, args...));
//}
//
//#endif