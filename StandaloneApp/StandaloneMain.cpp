#include <tchar.h>
#include"WndProcHandler.h"
#include "WindowUtils.h"
#include "Global.h"
#include "EventLoop.h"
#include "Logger.h"
#include "ExportFunctions.h"

// DLL header
#include "App.h"

#pragma comment (lib, "opengl32.lib")

void BindStdHandlesToConsole()
{
	// Redirect the CRT standard input, output, and error handles to the console
	FILE * tmp;

	freopen_s(&tmp, "CONIN$", "r", stdin);
	freopen_s(&tmp, "CONOUT$", "w", stdout);
	freopen_s(&tmp, "CONOUT$", "w", stderr);

	//Clear the error state for each of the C++ standard stream objects. We need to do this, as
	//attempts to access the standard streams before they refer to a valid target will cause the
	//iostream objects to enter an error state. In versions of Visual Studio after 2005, this seems
	//to always occur during startup regardless of whether anything has been read from or written to
	//the console or not.
	std::wcout.clear();
	std::cout.clear();
	std::wcerr.clear();
	std::cerr.clear();
	std::wcin.clear();
	std::cin.clear();
}

void SetConsole()
{
	if (AllocConsole())
	{
		BindStdHandlesToConsole();
	}
}


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	HINSTANCE GlobalHandleInstance = hInstance;

//#if _DEBUG

	SetConsole();

//#endif
	
	WNDCLASSA WindowClass = {};
	WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WindowClass.lpfnWndProc = MainWindowCallback;
	WindowClass.hInstance = hInstance;
	WindowClass.hCursor = LoadCursor(0, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WindowClass.lpszClassName = "MainAppWindowClass";
	WindowClass.lpszMenuName = NULL;

	int posx = (GetSystemMetrics(SM_CXSCREEN) / 2) - (500 / 2);
	int posy = (GetSystemMetrics(SM_CYSCREEN) / 2) - (500 / 2);


	if (RegisterClassA(&WindowClass))
	{
		HWND Window =
			CreateWindowExA(
				0, // WS_EX_TOPMOST|WS_EX_LAYERED,
				WindowClass.lpszClassName,
				"Engine v0.1",
				WS_OVERLAPPEDWINDOW,
				posx,
				posy,
				500,
				500,
				0,
				0,
				hInstance,
				0);

		if (Window)
		{
			//MakeFullScreen(Window);

			HWND MainWindow = Window;
			ShowWindow(Window, nCmdShow);

			App::Init(Window);

			return App::Start();
		}
	}

	return -1;
}
