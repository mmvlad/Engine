#include "DataParser.h"

#include "json.hpp"
#include "Logger.h"
#include "FileUtils.h"

using json = nlohmann::json;

std::vector<std::string> DataParser::GetSceneList()
{
	std::vector<std::string> sceneList;

	auto sceneListPath = FileUtils::CombinePath(PROJECT_DATA_DIR, SCENE_LIST_FILENAME);

	if (!FileUtils::FileExists(sceneListPath))
	{
		Log::Error("DataParser: Scene list file not found");
		return std::vector<std::string>();
	}

	auto jsonStr = FileUtils::StringFromFile(sceneListPath);
	json jsonList = json::parse(jsonStr.c_str());

	auto scenesNode = jsonList["scenes"];
	for (auto& element : scenesNode) {
		std::string sceneName = element.get<std::string>();
		sceneList.push_back(sceneName);

		Log::Info("Scene name: [" + element.get<std::string>() + "]");
	}

	return sceneList;
}

Scene* DataParser::LoadScene(const std::string& sceneName)
{
	auto scenesDir = FileUtils::CombinePath(PROJECT_DATA_DIR, SCENES_DIR);
	auto scenePath = FileUtils::CombinePath(scenesDir, sceneName + ".json"); //TODO(vlad): move extension from here

	if (!FileUtils::FileExists(scenePath))
	{
		Log::Error("Scene file not found [" + scenePath + "]");
		return nullptr;
	}

	using json		= nlohmann::json;
	auto jsonStr	= FileUtils::StringFromFile(scenePath);
	json jsonScene	= json::parse(jsonStr.c_str());

	Scene * scene = new Scene(sceneName);

	auto objects = jsonScene["objects"];
	for(auto object: objects)
	{
		//TODO(vlad): implement parsing gameobject with transform from scene file

		//GameObject * gameObject = new GameObject();

		//auto objectName = object["name"].get<std::string>();
		//gameObject->SetName(objectName);

		//auto components = object["components"];
		//for(auto component: components)
		//{
		//	auto type = component["componentName"];
		//	if (type == "MeshRenderer")
		//	{
		//		// handle mesh renderer
		//	}
		//}
	}

	return scene;
}
