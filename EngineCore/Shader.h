#pragma once

#include <string>
#include "Enums.h"
#include "Includes.h"

class Shader final
{

public:
	explicit Shader(const ShaderType & shaderType, const std::string & source);
	~Shader();


	const unsigned int	& Id()			const { return _id; }
	const ShaderType	& Type()		const { return _type; }
	const bool			& Inited()		const { return _inited; }
	
private:
	DISALLOW_COPY_AND_ASSIGN(Shader);

	void Compile()		const;
	bool HasCompiled()	const;

	ShaderType		_type;
	unsigned int	_id;
	bool			_inited;

};