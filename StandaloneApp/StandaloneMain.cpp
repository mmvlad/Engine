#include <tchar.h>
#include"WndProcHandler.h"
#include "WindowUtils.h"
#include "Global.h"
#include "EventLoop.h"
#include "Logger.h"

#pragma comment (lib, "opengl32.lib")

LRESULT CALLBACK TempCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return 0;
}


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	GlobalHandleInstance = hInstance;
	
	WNDCLASSA WindowClass = {};
	WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WindowClass.lpfnWndProc = MainWindowCallback;
	WindowClass.hInstance = hInstance;
	WindowClass.hCursor = LoadCursor(0, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WindowClass.lpszClassName = "MainAppWindowClass";
	WindowClass.lpszMenuName = NULL;


	if (RegisterClassA(&WindowClass))
	{
		HWND Window =
			CreateWindowExA(
				0, // WS_EX_TOPMOST|WS_EX_LAYERED,
				WindowClass.lpszClassName,
				"Kek",
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				0,
				0,
				hInstance,
				0);

		if (Window)
		{
			//MakeFullScreen(Window);

			MainWindow = Window;
			GlobalDeviceContext = GetDC(Window);
			GlobalOpenGlRenderContext = Win32InitOpenGL(GlobalDeviceContext);

			ReleaseDC(MainWindow, GlobalDeviceContext);
			ShowWindow(Window, nCmdShow);
		}
	}

	/*DestroyWindow(mainWindow);
	UnregisterClass(_T("mainWindowClass"), hInstance);

	if (!CreateNewWindow(_T("mainWindowClass"), _T("Main App"), MainWindowCallback, mainWindow))
	{
		Log::Error("Can't create window");

		return 1;
	}*/

	

	//MakeFullScreen(MainWindow);

	//HDC GlobalDeviceContext = GetDC(mainWindow);
	//HGLRC GlobalOpenGLRendercontetx = Win32InitOpenGL(GlobalDeviceContext, hInstance);

	//
	//CreateContext(mainWindow);

	

	return EventLoop();
}
