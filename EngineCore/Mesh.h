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

	const std::vector<glm::vec3> & Vertices()	const	{ return _vertexes; }
	const std::vector<glm::vec4> & Colors()		const	{ return _colors; }


private:
	DISALLOW_COPY_AND_ASSIGN(Mesh);

	std::vector<glm::vec3> _vertexes;
	std::vector<glm::vec4> _colors;
};

