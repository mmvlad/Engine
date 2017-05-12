#include "ShaderManager.h"
#include "FileUtils.h"
#include "Logger.h"
#include "json.hpp"
#include "Shader.h"

using json = nlohmann::json;

ShaderManager::ShaderManager()
{

}


ShaderManager::~ShaderManager()
{
	DeleteShaders();
}

void ShaderManager::Init()
{
	LoadShaderList();
	LoadShaders();
}

void ShaderManager::LoadShaderList()
{
	auto shaderListPath = FileUtils::CombinePath(CONFIG_DIR, SHADERS_FILENAME);

	if (!FileUtils::FileExists(shaderListPath))
	{
		Log::Error("ShaderManager: Shaders list file not found");
		return;
	}

	std::string jsonStr = FileUtils::StringFromFile(shaderListPath);

	json jsonList = json::parse(jsonStr.c_str());

	for (auto it = jsonList.begin(); it != jsonList.end(); ++it) {
		std::string shaderName = *it;
		_shaderList.push_back(shaderName);
		//Log::Info(shaderName);
	}

}

void ShaderManager::LoadShaders()
{
	auto shaderDir = FileUtils::CombinePath(CONFIG_DIR, SHADERS_DIR);

	for (auto it = _shaderList.begin(); it != _shaderList.end(); ++it) {
		std::string shaderName	= *it;
		
		auto vertexNameExt		= shaderName + VERTEX_EXT;
		auto fragmentNameExt	= shaderName + FRAGMENT_EXT;

		auto vertexPath			= FileUtils::CombinePath(shaderDir, vertexNameExt);
		auto fragmentPath		= FileUtils::CombinePath(shaderDir, fragmentNameExt);

		bool hasFiles			= true;

		if (!FileUtils::FileExists(vertexPath))
		{
			hasFiles = false;

			Log::Error("ShaderManager: Vertex shader file not found: " + vertexPath);
		}

		if (!FileUtils::FileExists(fragmentPath))
		{
			hasFiles = false;

			Log::Error("ShaderManager: Fragment shader file not found: " + fragmentPath);
		}

		if (hasFiles)
		{
			std::string vertexSource		= FileUtils::StringFromFile(vertexPath);
			std::string fragmentSource		= FileUtils::StringFromFile(fragmentPath);

			_vertexSaderMap[shaderName]		= new Shader(ShaderType::VERTEX_SHADER, vertexSource);
			_fragmentSaderMap[shaderName]	= new Shader(ShaderType::FRAGMENT_SHADER, fragmentSource);
		}
	}
}

void ShaderManager::DeleteShaders()
{
	for (auto it : _vertexSaderMap)
	{
		delete it.second;
	}

	for (auto it : _fragmentSaderMap)
	{
		delete it.second;
	}

	_vertexSaderMap.clear();
	_fragmentSaderMap.clear();
}
