#include "GlMaterial.h"

#include "GlProgram.h"
#include "Logger.h"
#include "GLWrap.h"
#include <gtc/type_ptr.hpp>

GlMaterial::GlMaterial(const ShaderManager * const shaderManager, const std::string & shaderName) :
	_shaderName		(shaderName),
	_shaderManager	(shaderManager)
{
	_program = new GlProgram();

	Load();
}

GlMaterial::~GlMaterial()
{
	delete _program;
}

void GlMaterial::Reload()
{
	Clear();
	Load();
}

void GlMaterial::Clear()
{
}

void GlMaterial::Load()
{
	auto vertexShader	= _shaderManager->GetVertexShader(_shaderName);
	auto fragmentShader = _shaderManager->GetFragmentShader(_shaderName);

	if (vertexShader == nullptr || fragmentShader == nullptr)
	{
		Log::Error("GL Material failed to load. One of shaders was not found");
		return;
	}

	_program->AttachShader(vertexShader);
	_program->AttachShader(fragmentShader);

	_program->Link();


	//TODO(vlad): detach/delete shaders here
}

void GlMaterial::SetMvpMatrix(glm::mat4 mvp)
{
	glUniformMatrix4fv(_program->MvpMatrixLocation(), 1, GL_FALSE, glm::value_ptr(mvp));
}
