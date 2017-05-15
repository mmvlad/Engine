#pragma once

#include "Includes.h"
#include <vector>
#include <string>
#include "Scene.h"

class BaseMeshManager;

class DataParser
{
public:
	static std::vector<std::string> GetSceneList();
	static Scene* LoadScene(const std::string & name, BaseMeshManager * meshManager);

private:
	DataParser();
	~DataParser();
};

