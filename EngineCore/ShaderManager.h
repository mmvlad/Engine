#pragma once

#include "Includes.h"
#include <vector>
#include <unordered_map>

class Shader;

//NOTE(vlad): Shader hot reload: https://gamedev.stackexchange.com/questions/124295/how-to-hot-reload-a-glsl-shader 

class ShaderManager
{
public:
	ShaderManager();
	virtual ~ShaderManager();

	void Init();

	const std::vector<std::string> & GetShaderList() const { return _shaderList; };

	const Shader * const GetVertexShader	(const std::string & name) const;
	const Shader * const GetFragmentShader	(const std::string & name) const;

private:
	void LoadShaderList();
	void LoadShaders();

	void DeleteShaders();

private:
	std::vector<std::string>					_shaderList;
	std::unordered_map<std::string, Shader*>	_vertexSaderMap;
	std::unordered_map<std::string, Shader*>	_fragmentSaderMap;
};

