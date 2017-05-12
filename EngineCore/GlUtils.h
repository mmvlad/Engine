#pragma once

#include "GlInfo.h"


void Resize(int width, int height);
GlInfo OpenGLGetInfo(bool ModernContext);


void glhPerspectivef2(float *matrix, float fovyInDegrees, float aspectRatio, float znear, float zfar);
void glhFrustumf2(float *matrix, float left, float right, float bottom, float top, float znear, float zfar);
