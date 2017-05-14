#include "SceneManager.h"
#include "FileUtils.h"
#include "DataParser.h"
#include <algorithm>
#include "Scene.h"

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	UnloadCurrentScene();
}

void SceneManager::Init()
{
	LoadSceneList();

}

void SceneManager::LoadSceneList()
{
	_sceneList = DataParser::GetSceneList();
}

void SceneManager::LoadScene(const std::string& sceneName)
{
	if (std::find(_sceneList.begin(), _sceneList.end(), sceneName) == _sceneList.end())
	{
		Log::Error("SceneManager: scene [" + sceneName + "] not found");
		return;
	}

	UnloadCurrentScene();

	_currentScene = DataParser::LoadScene(sceneName);
}

void SceneManager::UnloadCurrentScene()
{
	if (_currentScene)
	{
		delete _currentScene;

		_currentScene = nullptr;
	}
}
