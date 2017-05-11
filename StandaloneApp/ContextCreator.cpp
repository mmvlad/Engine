#include "ContextCreator.h"
#include "WindowUtils.h"
#include "WndProcHandler.h"
#include "Logger.h"

void ClearTrash();

void CreateContext(HWND handle)
{
	//NOTE(vlad): First - use standart pixel format to get opengl context
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		32,                        //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                        //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};


	HDC windowsDeviceContext = GetDC(handle);

	int  windowsPixelFormat = ChoosePixelFormat(windowsDeviceContext, &pfd);

	SetPixelFormat(windowsDeviceContext, windowsPixelFormat, &pfd);

	// Create openGl context
	HGLRC openGlRenderContext = wglCreateContext(windowsDeviceContext);

	if (!wglMakeCurrent(windowsDeviceContext, openGlRenderContext))
	{
		ErrorDialog("wglMakeCurrent opengl context error");
		return;
	}

	//NOTE(vlad): After context created and made current - init opengl extensions(load their pointers) with Glew
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		const char* errMsg = (char*)glewGetErrorString(err);

		Log::Error(errMsg);

		return;
	}

	InfoDialog((const char*)glGetString(GL_VERSION));

	int		suggestedPixelFormat	= 0;
	GLuint	numFormats				= 0;

	const int attribList[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		0,        //End
	};

	wglChoosePixelFormatARB(windowsDeviceContext, attribList, NULL, 1, &suggestedPixelFormat, &numFormats);

	bool modernContext = false;

	HGLRC sharedContext			= 0;
	//HGLRC modernGlRenderContext = wglCreateContextAttribsARB(windowsDeviceContext, sharedContext, )

	//NOTE(vlad): now we can query more advanced pixel format
	// after we have new pixel format - DESTROY old window as pixel format can't be changed
	// create new one and set needed format

	

	/*void* p = (void*)wglGetProcAddress("wglChoosePixelFormatARB");

	if (p == 0 ||
		(p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
		(p == (void*)-1))
	{
		MessageBoxA(0, "Extension not found", "OPENGL VERSION", 0);
	}
	else {
		MessageBoxA(0, "Extension found OK", "OPENGL VERSION", 0);
	}
*/
}


static bool wglChoosePixelFormatARBInited = false;


void DeleteOpenglContext(HGLRC openglContext)
{
	wglMakeCurrent(NULL, NULL);

	wglDeleteContext(openglContext);
}

int Win32OpenGLAttribs[] =
{
	WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
	WGL_CONTEXT_MINOR_VERSION_ARB, 0,
	WGL_CONTEXT_FLAGS_ARB, 0
	,
	WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
	0,
};

HGLRC Win32InitOpenGL(HDC WindowDC)
{
	LoadWglExtensions();

	bool ModernContext	= true;
	HGLRC OpenGLRC		= 0;

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		const char* errMsg = (char*)glewGetErrorString(err);
		//Log::Error(errMsg);
		Log::Error("Error initing glew");

		return 0;
	}

	//Log::Info("Glew inited OK");

	if (wglChoosePixelFormatARBInited)
	{
		Win32SetPixelFormat(WindowDC);

		OpenGLRC = wglCreateContextAttribsARB(WindowDC, 0, Win32OpenGLAttribs);
	}

	ClearTrash();

	if (!OpenGLRC)
	{
		ModernContext = false;
		OpenGLRC = wglCreateContext(WindowDC);
	}

	if (wglMakeCurrent(WindowDC, OpenGLRC))
	{
		/*if (wglSwapInterval)
		{
			wglSwapInterval(1);
		}*/
	}


	if (GLEW_OK != err)
	{
		const char* errMsg = (char*)glewGetErrorString(err);
		//Log::Error(errMsg);
		Log::Error("Error initing glew");

		return 0;
	}

	//Log::Info("Glew inited OK");

	return(OpenGLRC);
}

static HGLRC TempOpenGLRC;
static HWND TempWindow;
static HDC TempWindowDC;

void LoadWglExtensions()
{
	WNDCLASSA WindowClass = {};

	WindowClass.lpfnWndProc = DefWindowProcA;
	WindowClass.hInstance = GetModuleHandle(0);
	WindowClass.lpszClassName = "HandmadeWGLLoader";

	if (RegisterClassA(&WindowClass))
	{
		TempWindow = CreateWindowExA(
			0,
			WindowClass.lpszClassName,
			"TempWindow",
			0,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			0,
			0,
			WindowClass.hInstance,
			0);

		TempWindowDC = GetDC(TempWindow);
		Win32SetPixelFormat(TempWindowDC);

		TempOpenGLRC = wglCreateContext(TempWindowDC);
		if (wglMakeCurrent(TempWindowDC, TempOpenGLRC))
		{
			wglChoosePixelFormatARBInited = true;
		}

		//Trash will be cleaned after glew is inited
	}
	else
	{
		Log::Error("Can't create dummy window");
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

	if (wglChoosePixelFormatARBInited)
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
	}

	if (!ExtendedPick)
	{
		PIXELFORMATDESCRIPTOR DesiredPixelFormat = {};
		DesiredPixelFormat.nSize = sizeof(DesiredPixelFormat);
		DesiredPixelFormat.nVersion = 1;
		DesiredPixelFormat.iPixelType = PFD_TYPE_RGBA;
		DesiredPixelFormat.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
		DesiredPixelFormat.cColorBits = 32;
		DesiredPixelFormat.cAlphaBits = 8;
		DesiredPixelFormat.iLayerType = PFD_MAIN_PLANE;

		SuggestedPixelFormatIndex = ChoosePixelFormat(WindowDC, &DesiredPixelFormat);
	}

	//Log::Info("Suggested pixel format: %i", SuggestedPixelFormatIndex);

	PIXELFORMATDESCRIPTOR SuggestedPixelFormat;
	DescribePixelFormat(WindowDC, SuggestedPixelFormatIndex, sizeof(SuggestedPixelFormat), &SuggestedPixelFormat);
	SetPixelFormat(WindowDC, SuggestedPixelFormatIndex, &SuggestedPixelFormat);

}