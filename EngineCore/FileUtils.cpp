#include "FileUtils.h"
#include <Windows.h>
#include <fstream>

const std::string FileUtils::SEP = "\\";

FileUtils::FileUtils()
{
}


FileUtils::~FileUtils()
{
}

bool FileUtils::FileExists(const std::string& path)
{
	DWORD dwAttrib = GetFileAttributesA(path.c_str());

	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

std::string FileUtils::CombinePath(const std::string part1, const std::string part2)
{
	return part1 + SEP + part2;
}

std::string FileUtils::StringFromFile(const std::string& path)
{
	std::ifstream ifs(path);
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	return content;
}

