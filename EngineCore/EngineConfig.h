#pragma once

#include "Includes.h"
#include "IPrintable.h"
#include "json.hpp"

using json = nlohmann::json;

struct EngineConfig: IPrintable
{
	std::string EngineVersion;

	static EngineConfig FromJson(const std::string jsonStr)
	{
		EngineConfig resConfig;

		json config = json::parse(jsonStr.c_str());

		resConfig.EngineVersion = config["EngineVersion"].get<std::string>();

		return resConfig;
	}

	const std::string ToString() const override
	{
		return "Engine version: " + EngineVersion;
	}
};
