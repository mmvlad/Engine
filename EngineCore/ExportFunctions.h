#pragma once

#include "App.h"

extern "C" __declspec(dllexport)  void Init(HWND windowHandle);

extern "C" __declspec(dllexport)  void Start();

extern "C" __declspec(dllexport)  void Render();

extern "C" __declspec(dllexport)  void Tick();

extern "C" __declspec(dllexport)  void Resize(int width, int height);

extern "C" __declspec(dllexport)  void ReloadScene();

extern "C" __declspec(dllexport)  void ReloadScripts();