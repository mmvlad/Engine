#include "GlProgram.h"
#include "GLWrap.h"
#include "GlConfig.h"
#include "Shader.h"

GlProgram::GlProgram():
	_id(0),
	_hasLinked(false)
{
	_id = GLWrap::CreateShaderProgram();

	if (!Inited())
	{
		Log::Error("Failed to create shader program");
	}
}


GlProgram::~GlProgram()
{
	if (Inited())
	{
		GLWrap::DeleteProgram(_id);
	}
}

void GlProgram::AttachShader(const Shader* const shader)
{
	if (!Inited())
	{
		Log::Error("Can't attach shader to not inited program");
		return;
	}

	GLWrap::AttachShaderToProgram(shader->Id(), _id);
}

void GlProgram::Link()
{
	if (!Inited())
	{
		Log::Error("Can't link not inited program");
		return;
	}

	BindAttributes();

	GLWrap::LinkShaderProgram(_id);

	FindUniforms();

	_hasLinked = HasLinkedInternal();

	if (!_hasLinked)
	{
		auto log = GLWrap::GetShaderProgramInfoLog(_id);

		Log::Error("Program [" + std::to_string(_id) + "] failed to link.");
		Log::Error("Linking log: " + log);
	}
}

void GlProgram::Use()
{
	if (!Inited() || !HasLinked())
	{
		//Log::Error("Use(): Program with id [" + std::to_string(_id) + "] you are trying to use is not inited or failed to link");
		return;
	}

	GLWrap::UseShaderProgram(_id);
}

bool GlProgram::HasLinked() const
{
	return _hasLinked;
}

bool GlProgram::HasLinkedInternal() const
{
	GLint result = 0;
	GLWrap::GetShaderProgramInfo(_id, ShaderProgramInfoType::PROGRAM_LINK_STATUS, &result);
	return result == GL_TRUE;
}

void GlProgram::BindAttributes()
{
	GLWrap::BindShaderVariableLocation(_id, VERTEX_POSITION_LOCATION,	"in_vertex_position");
	GLWrap::BindShaderVariableLocation(_id, VERTEX_COLOR_LOCATION,		"in_vertex_color");
}

void GlProgram::FindUniforms()
{
	_mvpMatrixLocation = GLWrap::GetUniformVarLocation(_id, "in_mvp");
	if (_mvpMatrixLocation < 0)
	{
		Log::Error("GlProgram: mvp location not found in shader. Note: if it is not used, it was discarded by compiler");
	}

	Log::Info("mvp location: " + std::to_string(_mvpMatrixLocation));
}

