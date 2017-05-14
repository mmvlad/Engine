#include "MaterialManager.h"
#include "GlMaterial.h"
#include "Color.h"


MaterialManager::MaterialManager()
{
}

MaterialManager::~MaterialManager()
{
	delete _defaultMaterial;
}


void MaterialManager::Init(const ShaderManager* shaderManager)
{
	_shaderManager = shaderManager;

	_defaultMaterial = new GlMaterial(_shaderManager, "Diffuse");
}

