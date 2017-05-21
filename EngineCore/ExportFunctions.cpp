#include "ExportFunctions.h"

void Init(HWND windowHandle)
{
	App::Init(windowHandle);
	//MessageBoxA(NULL, "Inited", "InfoBox", NULL);
}

void Start()
{
	App::Start();
}

void Render()
{
	App::Render();
}

void Tick()
{
	App::ExecuteLogic();
}

void ReloadScene()
{
	App::ReloadScene();
}

void ReloadScripts()
{
	LuaBinding::ReloadScripts();
}

void Resize(int width, int height)
{
	glViewport(0, 0, width, height);
}
