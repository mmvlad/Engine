#include "FileUtils.h"
#include <Windows.h>
#include <fstream>
#include <codecvt>
#include "Logger.h"

#include <experimental/filesystem>

const std::string FileUtils::SEP = "\\";

std::wstring convert(const std::string& input)
{
	try
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(input);
	}
	catch (std::range_error& e)
	{
		size_t length = input.length();
		std::wstring result;
		result.reserve(length);
		for (size_t i = 0; i < length; i++)
		{
			result.push_back(input[i] & 0xFF);
		}
		return result;
	}
}

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

std::vector<std::string> FileUtils::GetFilesInDir(const std::string& dir)
{
	std::vector<std::string> fileNames;

	WIN32_FIND_DATAA search_data;

	memset(&search_data, 0, sizeof(WIN32_FIND_DATAA));

	HANDLE handle = FindFirstFileA(dir.c_str(), &search_data);

	while (handle != INVALID_HANDLE_VALUE)
	{
		std::string fileName(search_data.cFileName);

		if (fileName != "." && fileName != "..")
		{
			fileNames.push_back(search_data.cFileName);
		}

		if (FindNextFileA(handle, &search_data) == FALSE)
		{
			break;
		}
	}

	//Close the handle after use or memory/resource leak
	FindClose(handle);

	return fileNames;
}

std::string FileUtils::GetCurrentDir()
{
	std::string path = std::experimental::filesystem::current_path().string();
	return path;
}

