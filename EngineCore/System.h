#pragma once

#include "Includes.h"
#include "App.h"
#include "EngineConfig.h"

class System
{
public:
	static void OpenGlInfo();

	static void LoadConfig();

	static const EngineConfig & GetConfig() { return _config; }

public:
	virtual ~System();

private:
	System();
	DISALLOW_COPY_AND_ASSIGN(System);


private:
	static EngineConfig _config;
};

