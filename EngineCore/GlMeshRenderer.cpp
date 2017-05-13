#include "GlMeshRenderer.h"
#include "GLWrap.h"
#include "GlConfig.h"

GlMeshRenderer::GlMeshRenderer(Mesh & mesh, GlMaterial & material):
	_mesh		(mesh),
	_material	(material)
{
	InitVAO();
}

GlMeshRenderer::~GlMeshRenderer()
{
}

void GlMeshRenderer::Render()
{
	_material.Use();

	//NOTE(vlad): To draw wireframe try glPolygonMode(GL_FRONT, GL_LINE);

	GLWrap::BindVertexArray(_vao);

	Draw();
}

void GlMeshRenderer::InitVAO()
{
	GLWrap::GenVertexArrays(1, &_vao);
	GLWrap::BindVertexArray(_vao);

	// Setup position buffer
	GLWrap::GenBuffers(1, &_vertex_vbo);
	GLWrap::BindBuffers(BufferType::ARRAY_BUFFER, _vertex_vbo);
	GLWrap::FillBufferWithData(BufferType::ARRAY_BUFFER, _mesh.SizeBytes(), _mesh.StartPtr(), UsageType::STATIC_DRAW);

	// Setup position attribute
	GLWrap::VertexAttribPointer(VERTEX_POSITION_LOCATION, NumComponents::THREE, DataType::TYPE_FLOAT, false, 0, 0);
	GLWrap::EnableVertexAttribPointer(VERTEX_POSITION_LOCATION);

	//NOTE(vlad): Assume we always have vertex colors
	GLWrap::GenBuffers(1, &_colors_vbo);
	GLWrap::BindBuffers(BufferType::ARRAY_BUFFER, _colors_vbo);
	GLWrap::FillBufferWithData(BufferType::ARRAY_BUFFER, _mesh.SizeBytesColors(), _mesh.StartPtrColor(), UsageType::STATIC_DRAW);

	// Setup color attribute
	GLWrap::VertexAttribPointer(VERTEX_COLOR_LOCATION, NumComponents::FOUR, DataType::TYPE_FLOAT, false, 0, 0);
	GLWrap::EnableVertexAttribPointer(VERTEX_COLOR_LOCATION);

	
}

void GlMeshRenderer::Draw() const
{
	GLWrap::DrawArrays(DrawMode::MODE_TRIANGLES, 0, 3);
}
