#include "GameObject.h" 

#include <gtx/transform.hpp>
#include <gtx/euler_angles.hpp>


GameObject::GameObject(const std::string name, unsigned mesh, unsigned material):
	_name(name),
	_meshHandle(mesh),
	_materialHandle(material)
{

}

GameObject::~GameObject()
{

}

glm::mat4 GameObject::ModelMatrix() const
{
	return glm::translate(_position) * glm::eulerAngleXYZ(_rotation.x, _rotation.y, _rotation.z) * glm::scale(_scale);
}
