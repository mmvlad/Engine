#include "GlRender.h"
#include "GLWrap.h"
#include "GlMaterial.h"


GlRender::GlRender()
{
}


GlRender::~GlRender()
{
	delete _shaderManager;
	delete _materialManager;

	for(auto& mesh: _meshes)
	{
		delete mesh.second;
	}
}

void GlRender::Init(HDC* hdc, SceneManager * sceneManager)
{
	_hdc			= hdc;
	_sceneManager	= sceneManager;

	//NOTE(vlad): First - load extensions, THEN -> shader manager etc as they depend on them
	GLWrap::LoadExtensions();

	_shaderManager = new ShaderManager();
	_shaderManager->Init();

	_materialManager = new MaterialManager();
	_materialManager->Init(_shaderManager);
}

void GlRender::Render()
{
	GLWrap::SetClearColor(Color::FromHexRGB("20fb82"));
	GLWrap::ClearBuffer(ClearBufferType::COLOR_BUFFER);

	_materialManager->DefaultMaterial()->Use();

	// draw all objects from scene manager



	SwapBuffers(*_hdc);
}


void GlRender::RegisterMesh(const Mesh& mesh, unsigned id)
{
	//NOTE(vlad): Create graphics representation of mesh. after this mesh can actually be deleted
	_meshes[id] = new GlMesh(mesh);
}
