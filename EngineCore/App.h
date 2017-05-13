#pragma once

#include "LibHeader.h"
#include <Windows.h>

#include <GL/glew.h>
#include <GL/GL.h>
#include "EngineConfig.h"
#include "ShaderManager.h"
#include "MaterialManager.h"


class App
{
public:
	~App();

	static ENGINECORE_API int Start();
	static ENGINECORE_API void Init(HDC* hdc)	{ _hdc = hdc; }

private:
	App();

	static void Render();

	static void InitInternal();
	static void InitManagers();

private:
	static HDC				* _hdc;
	static ShaderManager	* _shaderManager;
	static MaterialManager	* _materialManager;
};

