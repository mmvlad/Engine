#pragma once

#include "Includes.h"
#include <vector>
#include "glm.hpp"

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	void AddVertex	(const glm::vec3 & vertex);
	void AddColor	(const glm::vec4 & color);
	void AddIndex	(int index);

	const std::vector<glm::vec3> & Vertices()	const	{ return _vertexes; }
	const std::vector<glm::vec4> & Colors()		const	{ return _colors; }
	const std::vector<int>		 & Indices()	const	{ return _indexes; }


private:
	DISALLOW_COPY_AND_ASSIGN(Mesh);

	std::vector<glm::vec3> _vertexes;
	std::vector<glm::vec4> _colors;
	std::vector<int> _indexes;
};

