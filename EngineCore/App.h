#pragma once

#include "LibHeader.h"
#include <Windows.h>

#include <GL/glew.h>
#include <GL/GL.h>



class App
{
public:
	~App();

	static ENGINECORE_API int Start();
	static ENGINECORE_API void Init(HDC* hdc) { _hdc = hdc; }


private:
	App();

	static void Render();

	static HDC* _hdc;
};

