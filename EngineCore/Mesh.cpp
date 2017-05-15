#include "Mesh.h"



Mesh::Mesh()
{

}



Mesh::~Mesh()
{
}

void Mesh::AddVertex(const glm::vec3 & vertex)
{
	_vertexes.push_back(vertex);
}

void Mesh::AddIndex(int index)
{
	_indexes.push_back(index);
}

void Mesh::AddColor(const glm::vec4& color)
{
	_colors.push_back(color);
}
