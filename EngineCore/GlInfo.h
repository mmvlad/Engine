#pragma once

#include "IPrintable.h"
#include <sstream>

struct GlInfo: public IPrintable
{
	
	bool ModernContext;

	char *Vendor;
	char *Renderer;
	char *Version;
	char *ShadingLanguageVersion;
	char *Extensions;

	const std::string ToString() const override
	{
		std::stringstream ss;
		ss	<< "OpenGL Info:" << std::endl 
			<< "Vendor: " << std::string(Vendor) << std::endl
			<< "Renderer: " << std::string(Renderer) << std::endl
			<< "Version: " << Version << std::endl
			<< "SL Version: " << ShadingLanguageVersion;
		
		return ss.str();
	}

	/*bool GL_EXT_texture_sRGB;
	bool GL_EXT_framebuffer_sRGB;*/
};

