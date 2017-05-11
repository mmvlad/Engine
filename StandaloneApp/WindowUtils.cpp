#include "WindowUtils.h"
#include "Global.h"
#include "Logger.h"
#include "WndProcHandler.h"

// Creates new win32 window and passes handle to _Out_ handle param
bool CreateNewWindow(_In_ const TCHAR* className, _In_ const TCHAR* windowName, _In_ WNDPROC winProc, _Out_ HWND & handle)
{

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = winProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GlobalHandleInstance;
	wcex.hIcon = LoadIcon(GlobalHandleInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = className;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	

	if (!RegisterClassEx(&wcex))
	{
		ErrorDialog("Failed to register window class");
		return false;
	}

	HWND hWnd = CreateWindow(
		className, // Application name
		windowName, // Application title
		WS_OVERLAPPEDWINDOW, // Type of widnow
		199, 199, // Initial position x,y
		500, 400, // width/height
		NULL, // parent
		NULL, // no menu bar
		GlobalHandleInstance, // winMain instance
		NULL // not used in this application
	);

	if (!hWnd)
	{
		ErrorDialog("Failed to create window");
		return false;
	}

	handle = hWnd;

	return true;
}

void ErrorDialog(const char* errorMsg)
{
	MessageBoxA(NULL, errorMsg, "ERROR", NULL);
}

void InfoDialog(const char* errorMsg)
{
	MessageBoxA(NULL, errorMsg, "INFO", NULL);
}

WINDOWPLACEMENT g_wpPrev = { sizeof(g_wpPrev) };

void MakeFullScreen(HWND hwnd)
{
	DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);
	if (dwStyle & WS_OVERLAPPEDWINDOW) {
		MONITORINFO mi = { sizeof(mi) };
		if (GetWindowPlacement(hwnd, &g_wpPrev) &&
			GetMonitorInfo(MonitorFromWindow(hwnd,
				MONITOR_DEFAULTTOPRIMARY), &mi)) {
			SetWindowLong(hwnd, GWL_STYLE,
				dwStyle & ~WS_OVERLAPPEDWINDOW);
			SetWindowPos(hwnd, HWND_TOP,
				mi.rcMonitor.left, mi.rcMonitor.top,
				mi.rcMonitor.right - mi.rcMonitor.left,
				mi.rcMonitor.bottom - mi.rcMonitor.top,
				SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		}
	}
	else {
		SetWindowLong(hwnd, GWL_STYLE,
			dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(hwnd, &g_wpPrev);
		SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
			SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
	}
}

