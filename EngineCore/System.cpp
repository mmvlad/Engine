#include "System.h"
#include "Logger.h"
#include "GlUtils.h"

System::System()
{
}


void System::OpenGlInfo()
{
	GlInfo glInfo = OpenGLGetInfo(true);
	Log::Info(glInfo.ToString());
}

System::~System()
{
}
