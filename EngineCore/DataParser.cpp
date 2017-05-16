#include "DataParser.h"

#include "json.hpp"
#include "Logger.h"
#include "FileUtils.h"
#include "BaseMeshManager.h"
#include "glm.hpp"

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

Scene* DataParser::LoadScene(const std::string& sceneName, BaseMeshManager * meshManager)
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
		auto objectName		= object["name"].get<std::string>();
		auto meshName		= object["mesh"].get<std::string>();
		auto materialName	= object["material"].get<std::string>();

		auto positionStr	= object["position"].get<std::string>();
		auto scaleStr		= object["scale"].get<std::string>();
		auto rotationStr	= object["rotation"].get<std::string>();

		glm::vec3 position	= Utils::VectorFromString(positionStr);
		glm::vec3 scale		= Utils::VectorFromString(scaleStr);
		glm::vec3 rotation	= Utils::VectorFromString(rotationStr);

		unsigned int meshId = meshManager->LoadMesh(meshName);

		//TODO(vlad): set material id or name
		unsigned int materialId = 1;

		std::vector<std::string> scripts;

		auto scriptsArr = object["scripts"];
		for(auto& scriptNameStr: scriptsArr)
		{
			scripts.push_back(scriptNameStr.get<std::string>());
		}

		GameObject * gameObject = new GameObject(objectName, meshId, materialId);
		gameObject->SetPosition(position);
		gameObject->SetScale(scale);
		gameObject->SetRotation(rotation);
		gameObject->SetScripts(scripts);

		scene->AddObject(gameObject);

		/*Log::Info("Obj name: " + objectName);
		Log::Info("Mesh name: " + meshName + ", handle [" + std::to_string(meshId) + "]");
		Log::Info("Material name: " + materialName);

		Log::Info("Position: [" + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(position.z) + "]");
		Log::Info("Scale: [" + std::to_string(scale.x) + ", " + std::to_string(scale.y) + ", " + std::to_string(scale.z) + "]");
		Log::Info("Rottion: [" + std::to_string(rotation.x) + ", " + std::to_string(rotation.y) + ", " + std::to_string(rotation.z) + "]");
	
		*/
	}

	return scene;
}
