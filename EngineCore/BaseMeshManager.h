#pragma once

#include "Mesh.h"
#include <unordered_map>
#include "GlRender.h"

class BaseMeshManager final
{
public:
	BaseMeshManager();
	~BaseMeshManager();

	void Init(GlRender * renderer);

public:
	unsigned int LoadMesh(const std::string meshName);

private:
	GlRender									  * _renderer;
	unsigned int									_nextMeshIndex;
	std::unordered_map<unsigned int, Mesh*>			_meshes;
	std::unordered_map<std::string, unsigned int>	_names;

};

