#pragma once

#include <string>
#include <vector>

class FileUtils
{
public:
	~FileUtils();

	static bool			FileExists		(const std::string & path);
	static std::string	CombinePath		(const std::string part1, const std::string part2);
	static std::string	StringFromFile	(const std::string & path);
	static std::vector<std::string> GetFilesInDir(const std::string & dir);
	static std::string GetCurrentDir();

public:

	static const std::string SEP;

private:
	FileUtils();
};

