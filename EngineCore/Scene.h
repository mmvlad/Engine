#pragma once
#include "Includes.h"
#include <string>
#include "GameObject.h"
#include <vector>
#include "SceneManager.h"
#include "Camera.h"

class Scene
{
public:
	explicit Scene(const std::string name);
	~Scene();

public:
	const std::string & GetName() const					{ return _name; }
	void AddObject(GameObject * object)					{ _objects.push_back(object); }
	const std::vector<GameObject*> & GetObjects() const { return _objects; }
	const Camera& DefaultCamera() const					{ return (*_defaultCamera); }

private:
	DISALLOW_COPY_AND_ASSIGN(Scene);

private:
	std::string					  _name;
	std::vector<GameObject*>	  _objects;
	Camera						* _defaultCamera;
};

