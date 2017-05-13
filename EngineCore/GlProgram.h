#pragma once

#include "Includes.h"

class Shader;

class GlProgram
{
public:
	GlProgram();
	virtual ~GlProgram();

	void AttachShader(const Shader * const shader);
	void Link();
	void Use();
	bool Inited()		const { return _id != 0; }
	unsigned int Id()	const { return _id; }
	bool HasLinked()	const;

private:
	bool HasLinkedInternal() const;
	void BindAttributes();

private:
	DISALLOW_COPY_AND_ASSIGN(GlProgram);

	unsigned int	_id;
	bool			_hasLinked;
};

