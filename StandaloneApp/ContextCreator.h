#pragma once

#include<Windows.h>
#include <GL\glew.h>
#include <GL\wglew.h>

#include<gl\GL.h>
#include<gl\GLU.h>

#include<iostream>


void DeleteOpenglContext(HGLRC openglContext);

void Win32SetPixelFormat(HDC WindowDC);

void LoadWglExtensions();

HGLRC Win32InitOpenGL(HDC WindowDC);
