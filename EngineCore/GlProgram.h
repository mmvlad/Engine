#pragma once

#include "Includes.h"

class Shader;



class GlProgram final
{
public:
	GlProgram();
	~GlProgram();

	void AttachShader(const Shader * const shader);
	void Link();
	void Use();

	bool Inited()			const { return _id != 0; }
	unsigned int Id()		const { return _id; }
	bool HasLinked()		const;
	int MvpMatrixLocation() const { return _mvpMatrixLocation; }

private:
	bool HasLinkedInternal() const;
	void BindAttributes();
	void FindUniforms();

private:
	DISALLOW_COPY_AND_ASSIGN(GlProgram);

	unsigned int	_id;
	bool			_hasLinked;
	int				_mvpMatrixLocation;
};

