#pragma once

#include <string>

class FileUtils
{
public:
	~FileUtils();

	static bool			FileExists		(const std::string & path);
	static std::string	CombinePath		(const std::string part1, const std::string part2);
	static std::string	StringFromFile	(const std::string & path);

public:

	static const std::string SEP;

private:
	FileUtils();
};

