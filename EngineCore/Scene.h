#pragma once
#include "Includes.h"
#include <string>
#include "GameObject.h"
#include <vector>
#include "SceneManager.h"

class Scene
{
public:
	explicit Scene(const std::string name);
	~Scene();

public:
	const std::string & GetName() const { return _name; }

	GameObject * FindObjectWithName(const std::string& name);

	void AddObject(GameObject * object) { _objects.push_back(object); }

private:
	DISALLOW_COPY_AND_ASSIGN(Scene);

private:
	std::string					_name;
	std::vector<GameObject*>	_objects;
};

