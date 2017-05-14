#include "GameObject.h"




GameObject::GameObject(const std::string name, unsigned mesh, unsigned material):
	_name(name),
	_meshHandle(mesh),
	_materialHandle(material)
{

}

GameObject::~GameObject()
{

}