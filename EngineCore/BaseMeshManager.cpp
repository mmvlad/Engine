#include "BaseMeshManager.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "FileUtils.h"
#include "Config.h"
#include "Logger.h"
#include "Color.h"

BaseMeshManager::BaseMeshManager():
	_nextMeshIndex(1)
{
	
}


BaseMeshManager::~BaseMeshManager()
{
	for(auto& mesh: _meshes)
	{
		delete mesh.second;
	}
}

void BaseMeshManager::Init(GlRender* renderer)
{
	_renderer = renderer;
}

unsigned BaseMeshManager::LoadMesh(const std::string meshName)
{
	if (_names.find(meshName) != _names.end())
	{
		Log::Info("Mesh manager: mesh already exists [" + meshName + "]");
		return _names[meshName];
	}

	auto modelsDir	= FileUtils::CombinePath(PROJECT_DATA_DIR, MODELS_DIR);
	auto fileName	= meshName + ".obj";
	auto meshPath	= FileUtils::CombinePath(modelsDir, fileName);
	
	if (!FileUtils::FileExists(meshPath))
	{
		Log::Error("MeshManager: mesh not found [" + meshPath + "]");
		return 0;
	}

	tinyobj::attrib_t attributes;
	std::vector<tinyobj::shape_t>		shapes;
	std::vector<tinyobj::material_t>	materials;

	std::string err;
	bool ret = tinyobj::LoadObj(&attributes, &shapes, &materials, &err, meshPath.c_str());

	if (!err.empty()) { // `err` may contain warning message.
		Log::Error("MeshManager: Error loading mesh [" + meshPath + "]");
		Log::Error("Error log: " + err);
		return 0;
	}

	if (!ret)
	{
		Log::Error("MeshManager: Error loading mesh [" + meshPath + "]");
		return 0;
	}

	if (shapes.size() == 0)
	{
		Log::Error("MeshManager: failed to load shape from .obj");
		return 0;
	}

	assert(attributes.vertices.size() % 3 == 0, "Element count must be %3 as these are vec3");

	Mesh * mesh = new Mesh();
	Log::Info("Loaded " + std::to_string(attributes.vertices.size()) + " vertices from model");

	int verticesElemCount = attributes.vertices.size() / 3;

	for (int i = 0; i < verticesElemCount; ++i)
	{
		float x = attributes.vertices[i * 3 + 0];
		float y = attributes.vertices[i * 3 + 1];
		float z = attributes.vertices[i * 3 + 2];

		mesh->AddVertex(glm::vec3(x, y, z));
		mesh->AddColor(Color::FromHexRGB("2870e2").ToVector()); //TODO(vlad): use vertex colors
	}

	for(int i = 0; i < shapes[0].mesh.indices.size(); ++i)
	{
		mesh->AddIndex(shapes[0].mesh.indices[i].vertex_index);
	}

	_meshes[_nextMeshIndex] = mesh;
	_names[meshName] = _nextMeshIndex;

	// Add to renderer
	_renderer->RegisterMesh((*mesh), _nextMeshIndex);

	//TODO(vlad): check, return _nextMeshIndex++ should wokr
	unsigned int res = _nextMeshIndex;
	_nextMeshIndex++;

	return res;
}
