#include "System.h"
#include "Logger.h"
#include "GlUtils.h"
#include "FileUtils.h"
#include "json.hpp"

EngineConfig System::_config = {};

using json = nlohmann::json;

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
	auto path = FileUtils::CombinePath(CONFIG_DIR, CONFIG_FILENAME);
	if (!FileUtils::FileExists(path))
	{
		Log::Error("Config file not found");
		return;
	}

	std::string jsonStr = FileUtils::StringFromFile(path);
	
	_config = EngineConfig::FromJson(jsonStr);

	Log::Info("Config: " + _config.ToString());
}

System::~System()
{
}
