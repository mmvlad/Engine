#include "ContextCreator.h"
#include "WindowUtils.h"
#include "Logger.h"


void Win32SetPixelFormat(HDC WindowDC);
void LoadWglExtensions();
void ClearTrash();

static bool WglChoosePixelFormatARBInited = false;
static HGLRC TempOpenGLRC;
static HWND TempWindow;
static HDC TempWindowDC;

int Win32OpenGLAttribs[] =
{
	WGL_CONTEXT_MAJOR_VERSION_ARB, 4, // Requesting opengl context version 4
	WGL_CONTEXT_MINOR_VERSION_ARB, 0,
	WGL_CONTEXT_FLAGS_ARB, 0
	,
	WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
	0,
};

std::string GetLastErrorAsString()
{
	//Get the error message, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0)
		return std::string(); //No error message has been recorded

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	std::string message(messageBuffer, size);

	//Free the buffer.
	LocalFree(messageBuffer);

	return message;
}

/**
 * \brief Inits opengl and returns opengl render context
 * \param WindowDC handle to window
 * \return opengl render context
 */
HGLRC Win32InitOpenGL(HDC WindowDC)
{
	LoadWglExtensions();

	// set is possible advanced pixel format fo MAIN window
	Win32SetPixelFormat(WindowDC);

	bool ModernContext	= true;
	HGLRC OpenGLRC		= 0;

	// Try create advanced opengl context
	if (WglChoosePixelFormatARBInited)
	{
		OpenGLRC = wglCreateContextAttribsARB(WindowDC, 0, Win32OpenGLAttribs);
	}

	ClearTrash();

	if (!OpenGLRC)
	{
		ModernContext	= false;
		OpenGLRC		= wglCreateContext(WindowDC);

		Log::Error("Couldn't create advanced opengl context, using regular");
		Log::Error("Last error: " + GetLastErrorAsString());
	}

	if (wglMakeCurrent(WindowDC, OpenGLRC))
	{
		Log::Info("Opengl context made current");

		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			const char* errMsg = (char*)glewGetErrorString(err);

			Log::Error("Error initing glew");
			Log::Error(errMsg);
		}

		/*if (wglSwapInterval)
		{
			wglSwapInterval(1);
		}*/
	} else
	{
		Log::Error("Failed to make opengl context current");
	}

	return(OpenGLRC);
}


// Creates temp window, sets basic pixel format, then loads extesnsions (Inits glew)
void LoadWglExtensions()
{
	WNDCLASSA WindowClass = {};

	WindowClass.lpfnWndProc		= DefWindowProcA;
	WindowClass.hInstance		= GetModuleHandle(0);
	WindowClass.lpszClassName	= "HandmadeWGLLoader";

	if (RegisterClassA(&WindowClass))
	{
		TempWindow = CreateWindowExA(
			0,
			WindowClass.lpszClassName,
			"TempWindow",
			0,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			500,
			500,
			0,
			0,
			WindowClass.hInstance,
			0);

		if (TempWindow)
		{
			TempWindowDC = GetDC(TempWindow);
			Win32SetPixelFormat(TempWindowDC);

			TempOpenGLRC = wglCreateContext(TempWindowDC);

			if (wglMakeCurrent(TempWindowDC, TempOpenGLRC))
			{
				WglChoosePixelFormatARBInited = true;

				GLenum err = glewInit();
				if (GLEW_OK != err)
				{
					const char* errMsg = (char*)glewGetErrorString(err);

					Log::Error("Error initing glew");
					Log::Error(errMsg);
				}
			}
		}

		//Temp window and etc will be cleaned after glew is inited
	}
	else
	{
		Log::Error("Can't create temp window");
	}
}

void ClearTrash()
{
	wglMakeCurrent(0, 0);
	wglDeleteContext(TempOpenGLRC);
	ReleaseDC(TempWindow, TempWindowDC);
	DestroyWindow(TempWindow);
}

void Win32SetPixelFormat(HDC WindowDC)
{
	int SuggestedPixelFormatIndex = 0;

	GLuint ExtendedPick = 0;

	// if extensions loaded (glew inited)
	if (WglChoosePixelFormatARBInited)
	{
		int IntAttribList[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB, GL_TRUE,
			0,
		};

		float FloatAttribList[] = { 0 };

		wglChoosePixelFormatARB(WindowDC, IntAttribList, FloatAttribList, 1, &SuggestedPixelFormatIndex, &ExtendedPick);

		Log::Info(string_format("Advanced pixel format [%i]", SuggestedPixelFormatIndex));
	}

	if (!ExtendedPick)
	{
		PIXELFORMATDESCRIPTOR DesiredPixelFormat	= {};
		DesiredPixelFormat.nSize					= sizeof(DesiredPixelFormat);
		DesiredPixelFormat.nVersion					= 1;
		DesiredPixelFormat.iPixelType				= PFD_TYPE_RGBA;
		DesiredPixelFormat.dwFlags					= PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
		DesiredPixelFormat.cColorBits				= 32;
		DesiredPixelFormat.cAlphaBits				= 8;
		DesiredPixelFormat.iLayerType				= PFD_MAIN_PLANE;

		SuggestedPixelFormatIndex = ChoosePixelFormat(WindowDC, &DesiredPixelFormat);

		Log::Info(string_format("Regular pixel format [%i]", SuggestedPixelFormatIndex));
	}

	PIXELFORMATDESCRIPTOR SuggestedPixelFormat;
	DescribePixelFormat(WindowDC, SuggestedPixelFormatIndex, sizeof(SuggestedPixelFormat), &SuggestedPixelFormat);
	if (!SetPixelFormat(WindowDC, SuggestedPixelFormatIndex, &SuggestedPixelFormat))
	{
		Log::Error("Failed to set pixel format");
		Log::Error("Last error: " + GetLastErrorAsString());
	}
}