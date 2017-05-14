#include "Scene.h"


Scene::Scene(const std::string name):
	_name(name)
{

}

Scene::~Scene()
{
	for(int i = 0; i < _objects.size(); ++i)
	{
		delete _objects[i];
	}
}
