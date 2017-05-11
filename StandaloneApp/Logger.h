#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <cstdio>

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
	size_t size = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	std::unique_ptr<char[]> buf(new char[size]);
	std::snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}


class Log
{
public:

	static void Info(const char* msg);
	static void Error(const char* msg);

	static void Info(const std::string & msg);
	static void Error(const std::string & msg);

	template<typename ... Args>
	static void Info(const std::string& format, Args&& ... args);

	template<typename ... Args>
	static void Error(const std::string& format, Args&& ... args);

private:
	Log();

	static void ShowDialog(const char* msg, const char* title);

};


template <typename ... Args>
void Log::Info(const std::string& format, Args&&... args)
{
	Log::Info(string_format(format, args...));
}

template <typename ... Args>
void Log::Error(const std::string& format, Args&&... args)
{
	Log::Error(string_format(format, args...));
}

