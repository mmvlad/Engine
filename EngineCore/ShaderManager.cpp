#include "ShaderManager.h"
#include "FileUtils.h"
#include "Logger.h"
#include "json.hpp"
#include "Shader.h"
#include "System.h"

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

const Shader* const ShaderManager::GetVertexShader(const std::string& name) const
{
	if (_vertexSaderMap.find(name) != _vertexSaderMap.end())
	{
		return _vertexSaderMap.at(name);
	}

	return nullptr;
}

const Shader* const ShaderManager::GetFragmentShader(const std::string& name) const
{
	if (_fragmentSaderMap.find(name) != _fragmentSaderMap.end())
	{
		return _fragmentSaderMap.at(name);
	}

	return nullptr;
}

void ShaderManager::LoadShaderList()
{
	auto shaderListPath = FileUtils::CombinePath(System::GetConfigDir(), SHADERS_FILENAME);

	if (!FileUtils::FileExists(shaderListPath))
	{
		Log::Error("ShaderManager: Shaders list file not found");
		return;
	}

	std::string jsonStr		= FileUtils::StringFromFile(shaderListPath);
	json		jsonList	= json::parse(jsonStr.c_str());

	for (auto it = jsonList.begin(); it != jsonList.end(); ++it) {
		std::string shaderName = *it;
		_shaderList.push_back(shaderName);
	}
}

void ShaderManager::LoadShaders()
{
	auto shaderDir = FileUtils::CombinePath(System::GetConfigDir(), SHADERS_DIR);

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
			//TODO(vlad): Add includes here from Includes dir with basic parameters
			std::string vertexSource		= FileUtils::StringFromFile(vertexPath);
			std::string fragmentSource		= FileUtils::StringFromFile(fragmentPath);

			Shader * vertexShader			= new Shader(ShaderType::VERTEX_SHADER, vertexSource);
			Shader * fragmentShader			= new Shader(ShaderType::FRAGMENT_SHADER, fragmentSource);

			if (!vertexShader->HasCompiled() || !fragmentShader->HasCompiled())
			{
				Log::Error("One of the shaders failed to compile. Shader [" + shaderName + "] wasn't loaded");

				delete vertexShader;
				delete fragmentShader;

				continue;
			}

			_vertexSaderMap[shaderName]		= vertexShader;
			_fragmentSaderMap[shaderName]	= fragmentShader;

			Log::Info("Shader [" + shaderName + "] loaded");
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
