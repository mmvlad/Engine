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

	// Vertexes
	const void * StartPtr()			const { return &_vertexes[0]; }
	unsigned int Size()				const { return _vertexes.size(); }
	unsigned int SizeBytes()		const { return  sizeof(glm::vec3) * _vertexes.size(); }

	// Color
	const void * StartPtrColor()	const { return &_colors[0]; }
	unsigned int SizeColors()		const { return _colors.size(); }
	unsigned int SizeBytesColors()	const { return  sizeof(glm::vec4) * _colors.size(); }

private:
	DISALLOW_COPY_AND_ASSIGN(Mesh);

	std::vector<glm::vec3> _vertexes;
	std::vector<glm::vec4> _colors;


};

