#pragma once

#include "Includes.h"

class ShaderManager;
class GlMaterial;

class MaterialManager
{
private:
	APP_MANAGER(MaterialManager);


public:
	virtual ~MaterialManager();

	void Init(const ShaderManager * shaderManager);


private:
	const ShaderManager * _shaderManager;
	GlMaterial			* _defaultMaterial;
};

