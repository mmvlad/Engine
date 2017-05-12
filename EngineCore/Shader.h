#pragma once

#include <string>
#include "Enums.h"
#include "Includes.h"

class Shader
{

public:
	explicit Shader(const ShaderType & shaderType, const std::string & source);

	// Shader object can be deleted after it is attached to the program
	virtual ~Shader();

	
public:
	const unsigned int	Id()		const { return _id; }
	const ShaderType	Type()		const { return _type; }
	const bool			Inited()	const { return _inited; }

private:
	bool HasCompiled()	const;
	void Compile()		const;

private:
	DISALLOW_COPY_AND_ASSIGN(Shader);

	ShaderType		_type;
	unsigned int	_id;
	bool			_inited;

};