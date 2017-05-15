#pragma once

#include "Includes.h"
#include "Mesh.h"
#include <unordered_map>
#include "GlMesh.h"
#include <Windows.h>
#include "ShaderManager.h"
#include "MaterialManager.h"

class SceneManager;

class GlRender final
{
public:
	GlRender();
	~GlRender();

	
public:

	void Init(HDC * hdc, SceneManager * sceneManager);

	void Resize(int witdth, int height);

	void Render();

	void RegisterMesh(const Mesh & mesh, unsigned int id);


private:
	DISALLOW_COPY_AND_ASSIGN(GlRender);

private:
	std::unordered_map<unsigned int, GlMesh*>	  _meshes;
	HDC											* _hdc;
	SceneManager								* _sceneManager;
	ShaderManager								* _shaderManager;
	MaterialManager								* _materialManager;
};

