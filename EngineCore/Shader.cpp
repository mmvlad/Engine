#include "Shader.h"
#include "Logger.h"
#include "GLWrap.h"


Shader::Shader(const ShaderType & shaderType, const std::string& source):
	_type(shaderType)
{
	_id = GLWrap::CreateShaderObject(shaderType);

	// Set source code for this shader
	GLWrap::AddShaderSource(_id, source);

	Compile();

	_inited = HasCompiled();
	
}

Shader::~Shader()
{
	GLWrap::DeleteShaderObject(_id);
}

void Shader::Compile() const
{
	GLWrap::CompileShaderObject(_id);

	if (!HasCompiled())
	{
		auto log = GLWrap::GetShaderObjectInfoLog(_id);

		Log::Error("Shader has not compiled (id: " + std::to_string(_id) + ")");
		Log::Error("Compilation log: " +log);
	}
}

bool Shader::HasCompiled() const
{
	GLint result = 0;
	GLWrap::GetShaderObjectInfo(_id, ShaderInfoType::SHADER_COMPILE_STATUS, &result);
	return result == GL_TRUE;
}
