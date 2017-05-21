#include "System.h"
#include "Logger.h"
#include "GlUtils.h"
#include "FileUtils.h"
#include "json.hpp"

using json = nlohmann::json;

EngineConfig	System::_config		= {};
std::string		System::_projectDir;

System::System()
{
	
}


void System::OpenGlInfo()
{
	GlInfo glInfo = OpenGLGetInfo(true);
	Log::Info(glInfo.ToString());
}

void System::LoadConfig()
{
	auto path = FileUtils::CombinePath(System::GetConfigDir(), CONFIG_FILENAME);
	if (!FileUtils::FileExists(path))
	{
		Log::Error("Config file not found");
		return;
	}

	std::string jsonStr = FileUtils::StringFromFile(path);
	
	_config = EngineConfig::FromJson(jsonStr);

	Log::Info("Config: " + _config.ToString());
}

void System::SetDefaultProjectDir()
{
	if (_projectDir == "")
	{
		// Default project dir: where process is
		System::SetProjectDir(FileUtils::GetCurrentDir());
	}
}

System::~System()
{
}
