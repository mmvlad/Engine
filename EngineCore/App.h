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
	static ENGINECORE_API void Init(HWND hwnd)	{ _hwnd = hwnd; }

	static void Render();

private:
	App();

	static void InitInternal();
	static void InitManagers();
	

private:
	static HWND				  _hwnd;
	static HDC				  _hdc;
	static SceneManager		* _sceneManager;
	static GlRender			* _renderer;
	static BaseMeshManager	* _meshManager;
};

