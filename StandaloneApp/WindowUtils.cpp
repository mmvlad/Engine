#include "WindowUtils.h"
#include "Global.h"
#include "Logger.h"
#include "WndProcHandler.h"


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

