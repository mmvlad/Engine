#pragma once

#include "App.h"

extern "C" __declspec(dllexport)  void Init(HWND windowHandle);

extern "C" __declspec(dllexport)  void Start();

extern "C" __declspec(dllexport)  void Render();

extern "C" __declspec(dllexport)  void Resize(int width, int height);