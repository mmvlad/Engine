#pragma once


#include <memory>
#include <iostream>
#include <string>
#include <cstdio>
#include "glm.hpp"
#include <iterator>
#include <vector>
#include <sstream>
#include <cstdlib>

std::string ReadFile(const std::string & path);

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
	size_t size = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	std::unique_ptr<char[]> buf(new char[size]);
	std::snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}


namespace Utils
{
	//NOTE(vlad): help struct to split strings
	struct tokens : std::ctype<char>
	{
		tokens() : std::ctype<char>(get_table()) {}

		static std::ctype_base::mask const* get_table();
	};

	std::vector<std::string> SplitStrByComma(const std::string& str);


	glm::vec3 VectorFromString(const std::string & str);
	

}