#pragma once

#include "Includes.h"
#include <string>
#include <vector>
#include "glm.hpp"

//NOTE(vlad): This represents object in game(basically mesh renderer). players scripts must reffer to it by name(handle)
class GameObject
{
public:
	GameObject(const std::string name, unsigned int mesh, unsigned int material);
	virtual ~GameObject();

public:
	const std::string & GetName()		const { return _name; }
	unsigned int		GetMaterial()	const { return _materialHandle; }
	unsigned int		GetMesh()		const { return _meshHandle; }

	const glm::vec3 &	Position()		const { return _position; }
	const glm::vec3 &	Scale()			const { return _scale; }
	const glm::vec3 &	Rotation()		const { return _rotation; }

	void SetPosition(const glm::vec3 position)	{ _position = position; }
	void SetScale	(const glm::vec3 scale)		{ _scale	= scale; }
	void SetRotation(const glm::vec3 rotation)	{ _rotation = rotation; }

private:
	DISALLOW_COPY_AND_ASSIGN(GameObject);

private:
	std::string		_name;
	unsigned int	_meshHandle;
	unsigned int	_materialHandle;

	glm::vec3 _position;
	glm::vec3 _scale;
	glm::vec3 _rotation;
};

