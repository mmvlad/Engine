#define _USE_MATH_DEFINES
#include <math.h>

#include "GlUtils.h"
#include "GLWrap.h"

//inline void
//OpenGLSetScreenspace(int Width, int Height)
//{
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	glMatrixMode(GL_PROJECTION);
//	float a = SafeRatio1(2.0f, (float)Width);
//	float b = SafeRatio1(2.0f, (float)Height);
//	GLfloat Proj[] =
//	{
//		a,  0,  0,  0,
//		0,  b,  0,  0,
//		0,  0,  1,  0,
//		-1, -1,  0,  1,
//	};
//	glLoadMatrixf(Proj);
//}

void gluPerspectiveCustom(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	GLdouble m[4][4] = {0};
	double sine, cotangent, deltaZ;
	double radians = fovy / 2 * M_PI / 180;

	deltaZ = zFar - zNear;
	sine = sin(radians);
	if ((deltaZ == 0) || (sine == 0) || (aspect == 0)) {
		return;
	}
	cotangent = cos(radians) / sine;

	//__gluMakeIdentityd(&m[0][0]);
	m[0][0] = cotangent / aspect;
	m[1][1] = cotangent;
	m[2][2] = -(zFar + zNear) / deltaZ;
	m[2][3] = -1;
	m[3][2] = -2 * zNear * zFar / deltaZ;
	m[3][3] = 0;
	glMultMatrixd(&m[0][0]);
}


void Resize(int width, int height)
{
	if (height <= 0) height = 1;
	int aspectratio = width / height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float* martix = new float[16];

	glhPerspectivef2(martix, 45.0f, aspectratio, 0.2f, 255.0f);

	glMultMatrixd((double*)martix);

	//gluPerspectiveCustom(45.0f, aspectratio, 0.2f, 255.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	delete[] martix;
}
void glhFrustumf2(float *matrix, float left, float right, float bottom, float top,
	float znear, float zfar)
{
	float temp, temp2, temp3, temp4;
	temp = 2.0 * znear;
	temp2 = right - left;
	temp3 = top - bottom;
	temp4 = zfar - znear;
	matrix[0] = temp / temp2;
	matrix[1] = 0.0;
	matrix[2] = 0.0;
	matrix[3] = 0.0;
	matrix[4] = 0.0;
	matrix[5] = temp / temp3;
	matrix[6] = 0.0;
	matrix[7] = 0.0;
	matrix[8] = (right + left) / temp2;
	matrix[9] = (top + bottom) / temp3;
	matrix[10] = (-zfar - znear) / temp4;
	matrix[11] = -1.0;
	matrix[12] = 0.0;
	matrix[13] = 0.0;
	matrix[14] = (-temp * zfar) / temp4;
	matrix[15] = 0.0;
}

void glhPerspectivef2(float *matrix, float fovyInDegrees, float aspectRatio, float znear, float zfar)
{
	float ymax, xmax;
	float temp, temp2, temp3, temp4;
	ymax = znear * tanf(fovyInDegrees * M_PI / 360.0);
	//ymin = -ymax;
	//xmin = -ymax * aspectRatio;
	xmax = ymax * aspectRatio;
	glhFrustumf2(matrix, -xmax, xmax, -ymax, ymax, znear, zfar);
}

inline bool
IsEndOfLine(char C)
{
	bool Result = ((C == '\n') ||
		(C == '\r'));

	return(Result);
}

inline bool
IsWhitespace(char C)
{
	bool Result = ((C == ' ') ||
		(C == '\t') ||
		(C == '\v') ||
		(C == '\f') ||
		IsEndOfLine(C));

	return(Result);
}

GlInfo OpenGLGetInfo(bool ModernContext)
{
	GlInfo Result = {};

	Result.ModernContext	= ModernContext;
	Result.Vendor			= (char *)glGetString(GL_VENDOR);
	Result.Renderer			= (char *)glGetString(GL_RENDERER);
	Result.Version			= (char *)glGetString(GL_VERSION);

	if (Result.ModernContext)
	{
		Result.ShadingLanguageVersion = (char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
	}
	else
	{
		Result.ShadingLanguageVersion = "(none)";
	}

	Result.Extensions = (char *)glGetString(GL_EXTENSIONS);

	/*char *At = Result.Extensions;
	while (*At)
	{
		while (IsWhitespace(*At)) { ++At; }
		char *End = At;
		while (*End && !IsWhitespace(*End)) { ++End; }

		umm Count = End - At;

		if (0) {}
		else if (StringsAreEqual(Count, At, "GL_EXT_texture_sRGB")) { Result.GL_EXT_texture_sRGB = true; }
		else if (StringsAreEqual(Count, At, "GL_EXT_framebuffer_sRGB")) { Result.GL_EXT_framebuffer_sRGB = true; }

		At = End;
	}*/

	return(Result);
}