#pragma once

#include "Includes.h"
#include "App.h"
#include "EngineConfig.h"
#include "Config.h"
#include "FileUtils.h"

class System
{
public:
	static void OpenGlInfo();

	static void LoadConfig();

	static const EngineConfig & GetConfig() { return _config; }

	static void SetProjectDir(const std::string & dir) { _projectDir = dir; }

	static const std::string & GetProjectDir() { return _projectDir; }
	
	static std::string GetConfigDir() { return FileUtils::CombinePath(_projectDir, CONFIG_DIR); }

	static std::string GetProjectDataDir() { return FileUtils::CombinePath(_projectDir, PROJECT_DATA_DIR); }

	static void SetDefaultProjectDir();



public:
	virtual ~System();

private:
	System();
	DISALLOW_COPY_AND_ASSIGN(System);


private:
	static EngineConfig	_config;
	static std::string	_projectDir;
};

