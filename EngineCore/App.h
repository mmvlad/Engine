#pragma once

#include "LibHeader.h"
#include <Windows.h>

#include <GL/glew.h>
#include <GL/GL.h>
#include "SceneManager.h"
#include "GlRender.h"
#include "BaseMeshManager.h"


class App
{
public:
	~App();

	static ENGINECORE_API int Start();
	static ENGINECORE_API void Init(HDC* hdc)	{ _hdc = hdc; }

private:
	App();

	static void InitInternal();
	static void InitManagers();

private:
	//NOTE(vlad): HDC is not used for now
	static HDC				* _hdc;
	static SceneManager		* _sceneManager;
	static GlRender			* _renderer;
	static BaseMeshManager	* _meshManager;
};

