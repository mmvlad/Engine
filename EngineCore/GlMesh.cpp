#include "GlMesh.h"
#include "GLWrap.h"
#include "GlConfig.h"


GlMesh::GlMesh(const Mesh& mesh)
{
	_vertexCount = mesh.Vertices().size();

	GLWrap::GenVertexArrays(1, &_vao);
	GLWrap::BindVertexArray(_vao);

	// Setup position buffer
	GLWrap::GenBuffers(1, &_vertex_vbo);
	GLWrap::BindBuffers(BufferType::ARRAY_BUFFER, _vertex_vbo);
	GLWrap::FillBufferWithData(BufferType::ARRAY_BUFFER, mesh.Vertices().size() * sizeof(glm::vec3), &mesh.Vertices().front(), UsageType::STATIC_DRAW);

	// Setup position attribute
	GLWrap::VertexAttribPointer(VERTEX_POSITION_LOCATION, NumComponents::THREE, DataType::TYPE_FLOAT, false, 0, 0);
	GLWrap::EnableVertexAttribPointer(VERTEX_POSITION_LOCATION);


	//NOTE(vlad): Assume we always have vertex colors
	GLWrap::GenBuffers(1, &_colors_vbo);
	GLWrap::BindBuffers(BufferType::ARRAY_BUFFER, _colors_vbo);
	GLWrap::FillBufferWithData(BufferType::ARRAY_BUFFER, mesh.Colors().size() * sizeof(glm::vec4), &mesh.Colors().front(), UsageType::STATIC_DRAW);

	// Setup color attribute
	GLWrap::VertexAttribPointer(VERTEX_COLOR_LOCATION, NumComponents::FOUR, DataType::TYPE_FLOAT, false, 0, 0);
	GLWrap::EnableVertexAttribPointer(VERTEX_COLOR_LOCATION);


	// Unbind VAO
	GLWrap::BindVertexArray(0);
}

GlMesh::~GlMesh()
{
	//NOTE(vlad): should be ok to delete them after binding to VAO
	GLWrap::DeleteBuffers(1, &_vertex_vbo);
	GLWrap::DeleteBuffers(1, &_colors_vbo);

	GLWrap::DeleteVertexArrays(1, &_vao);
}
