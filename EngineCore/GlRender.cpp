#include "GlRender.h"
#include "GLWrap.h"
#include "GlMaterial.h"
#include "SceneManager.h"
#include "Scene.h"
#include "glm.hpp"

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

void GlRender::Resize(int witdth, int height)
{
	//glViewport(0, 0, witdth, height);

	/*glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	float Proj[] =
	{
		500,  0,  0,  0,
		0,  500,  0,  0,
		0,  0,  1,  0,
		-1, -1,  0,  1,
	};
	glLoadMatrixf(Proj);*/
}

void GlRender::Render()
{
	//TODO(vlad): take color from camera back color
	GLWrap::SetClearColor(Color::FromHexRGB("20fb82"));
	GLWrap::ClearBuffer(ClearBufferType::COLOR_BUFFER);

	Scene * scene = _sceneManager->ActiveScene();
	Camera camera = scene->DefaultCamera();

	// Draw all objects from scene manager
	for(auto& gameObject: scene->GetObjects())
	{
		auto internalMesh = _meshes[gameObject->GetMesh()];

		//TODO(vlad): use material from game object (by handle etc)
		_materialManager->DefaultMaterial()->Use();

		// Set matrices
		//TODO(vlad): move matrix calculation away, leave only seeting data to shaders
		glm::mat4 mvp = camera.ProjectionMatrix() * camera.ViewMatrix() * gameObject->ModelMatrix();
		_materialManager->DefaultMaterial()->SetMvpMatrix(mvp);

		GLWrap::BindVertexArray(internalMesh->Vao());
		//GLWrap::DrawArrays(DrawMode::MODE_TRIANGLES, 0, internalMesh->VertexCount());
		glDrawElements(GL_TRIANGLES, internalMesh->VertexCount(), GL_UNSIGNED_INT, (void*)0);
	}


	SwapBuffers(*_hdc);
}


void GlRender::RegisterMesh(const Mesh& mesh, unsigned id)
{
	//NOTE(vlad): Create graphics representation of mesh. after this mesh can actually be deleted
	_meshes[id] = new GlMesh(mesh);
}
