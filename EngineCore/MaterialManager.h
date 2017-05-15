#pragma once

#include "Includes.h"

class ShaderManager;
class GlMaterial;

class MaterialManager final
{

public:
	MaterialManager();
	~MaterialManager();

	void Init(const ShaderManager * shaderManager);

	GlMaterial * DefaultMaterial() { return _defaultMaterial; }

private:
	const ShaderManager * _shaderManager;
	GlMaterial			* _defaultMaterial;
};

