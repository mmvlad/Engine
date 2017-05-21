#include "ExportFunctions.h"
#include "System.h"

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

void SetProjectDir(const char* path)
{
	System::SetProjectDir(path);
}

void Resize(int width, int height)
{
	glViewport(0, 0, width, height);
}
