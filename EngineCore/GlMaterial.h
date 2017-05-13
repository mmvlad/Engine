#pragma once

#include "Includes.h"
#include <string>
#include "ShaderManager.h"
#include "GlProgram.h"
#include <unordered_map>

class GlMaterial
{
public:
	explicit GlMaterial(const ShaderManager * const shaderManager, const std::string & shaderName);

	virtual ~GlMaterial();

	void Reload();

	void Use() const { _program->Use(); }


private:
	void Clear();
	void Load();

private:
	DISALLOW_COPY_AND_ASSIGN(GlMaterial);

	GlProgram * _program;
	std::string _shaderName;

	const ShaderManager * const _shaderManager;
};

