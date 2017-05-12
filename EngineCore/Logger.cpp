#include "Logger.h"



Log::Log()
{
	// private constructor
}

void Log::Info(const char* msg)
{
	std::cout << "INFO: " << msg << std::endl;
	//ShowDialog(msg, "INFO");
}

void Log::Error(const char* msg)
{
	std::cout << "ERROR: " << msg << std::endl;
	//ShowDialog(msg, "ERROR");
}

void Log::Info(const std::string& msg)
{
	Log::Info(msg.c_str());
}

void Log::Error(const std::string& msg)
{
	Log::Error(msg.c_str());
}


