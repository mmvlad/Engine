#pragma once

#include "Includes.h"
#include  "json.hpp"
#include <vector>
#include <string>
#include "Logger.h"
//#include "Scene.h"

class Scene;

class SceneManager
{
private:
	APP_MANAGER(SceneManager);

public:
	virtual ~SceneManager();

	void Init();
	void LoadSceneList();
	void LoadScene(const std::string & sceneName);

private:
	void UnloadCurrentScene();

private:
	std::vector<std::string> _sceneList;
	Scene * _currentScene;
};

