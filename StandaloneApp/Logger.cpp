#include "Logger.h"
#include <Windows.h>

Log::Log()
{
	// private constructor
}

void Log::Info(const char* msg)
{
	ShowDialog(msg, "INFO");
}

void Log::Error(const char* msg)
{
	ShowDialog(msg, "ERROR");
}

void Log::Info(const std::string& msg)
{
	Log::Info(msg.c_str());
}

void Log::Error(const std::string& msg)
{
	Log::Error(msg.c_str());
}

void Log::ShowDialog(const char* msg, const char* title)
{
	MessageBoxA(NULL, msg, title, NULL);
}


