#pragma once

#include "Includes.h"
#include "Mesh.h"

class GlMesh
{
public:
	explicit GlMesh(const Mesh & mesh);
	~GlMesh();

	unsigned int Vao()			const { return _vao; }
	unsigned int VertexCount()	const { return _vertexCount; }

private:
	DISALLOW_COPY_AND_ASSIGN(GlMesh);

private:
	unsigned int	_vao;
	unsigned int	_vertexCount;

	//NOTE(vlad): Don't actually need these
	unsigned int	_vertex_vbo;
	unsigned int	_colors_vbo;
	unsigned int	_indexBuffer;
};

