#pragma once

#include "Includes.h"
#include  "json.hpp"
#include <vector>
#include <string>
#include "Logger.h"


class Scene;
class BaseMeshManager;

class SceneManager final
{
public:
	SceneManager();

	virtual ~SceneManager();

	void Init(BaseMeshManager * meshManager);
	void LoadSceneList();
	void LoadScene(const std::string & sceneName);

private:
	void UnloadCurrentScene();

private:
	std::vector<std::string>	  _sceneList;
	Scene						* _currentScene;
	BaseMeshManager				* _meshManager;
};

