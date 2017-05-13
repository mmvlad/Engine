#pragma once

#include "Includes.h"
#include "Mesh.h"
#include "GlMaterial.h"
#include "IRenderable.h"

class GlMeshRenderer: public IRenderable
{
public:
	explicit GlMeshRenderer(Mesh& mesh, GlMaterial& material);
	virtual ~GlMeshRenderer();

	void Render() override;

private:
	void InitVAO();
	void Draw() const;

private:
	DISALLOW_COPY_AND_ASSIGN(GlMeshRenderer);

	Mesh		&	_mesh;
	GlMaterial	&	_material;
	unsigned int	_vao;
	unsigned int	_vertex_vbo;
	unsigned int	_colors_vbo;
};

