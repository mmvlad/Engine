#pragma once

#include "ContextCreator.h"
#include <tchar.h>

bool CreateNewWindow(_In_ const TCHAR* className, _In_ const TCHAR* windowName, _In_ WNDPROC winProc, _Out_ HWND & handle);

void ErrorDialog(const char* errorMsg);

void InfoDialog(const char* errorMsg);

void MakeFullScreen(HWND hwnd);