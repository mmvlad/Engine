#pragma once

#include <GL\glew.h>
#include <Gl\GL.h>

#include "Color.h"
#include "Enums.h"

#define BUFFER_OFFSET(offset) ((void *)(offset))


class GLWrap
{
public:

	static void LoadExtensions()
	{
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			const char* errMsg = (char*)glewGetErrorString(err);

			Log::Error("Error initing glew");
			Log::Error(errMsg);
		}
	}

	/*
	** Returns n currently unused names for use as vertex-array objects in the
	** array arrays. The names returned are marked as used for the purposes
	** of allocating additional buffer objects, and initialized with values
	** representing the default state of the collection of uninitialized vertex
	** arrays.
	*/
	static void GenVertexArrays(const GLuint count, GLuint * arrs) {
		glGenVertexArrays(count, arrs);
	}

	/*
	** Deletes the N vertex-arrays objects specified in arrays, enabling the names
	** for reuse as vertex arrays later. If a bound vertex array is deleted, the
	** bindings for that vertex array become zero (as if you had called
	** glBindBuffer() with a value of zero) and the default vertex array becomes
	** the current one. Unused names in arrays are released, but no changes to
	** the current vertex array state are made.
	*/
	static void DeleteVertexArrays(const GLuint count, GLuint * arrs) {
		glDeleteVertexArrays(count, arrs);
	}


	/*
	** glBindVertexArray() does three things. When using the value array that
	** is other than zero and was returned from glGenVertexArrays(), a new
	** vertex-array object is created and assigned that name. When binding to a
	** previously created vertex-array object, that vertex array object becomes
	** active, which additionally affects the vertex array state stored in the
	** object. When binding to an array value of zero, OpenGL stops using
	** application-allocated vertex-array objects and returns to the default state
	** for vertex arrays.
	** A GL_INVALID_OPERATION error is generated if array is not a value
	** previously returned from glGenVertexArrays(), or if it is a value that has
	** been released by glDeleteVertexArrays().
	*/
	static void BindVertexArray(const GLuint index) {
		glBindVertexArray(index);
	}

	static void UnBindVertexArray() {
		glBindVertexArray(0);
	}

	/*
	** Returns GL_TRUE if array is the name of a vertex-array object that was
	** previously generated with glGenVertexArrays(), but has not been
	** subsequently deleted. Returns GL_FALSE if array is zero or a nonzero
	** value that is not the name of a vertex-array object.
	*/
	static GLboolean IsVertexArray(const GLuint index) {
		return glIsVertexArray(index);
	}

	/*
	** Returns n currently unused names for buffer objects in the array buffers.
	** The names returned in buffers do not have to be a contiguous set of
	** integers.
	** The names returned are marked as used for the purposes of allocating
	** additional buffer objects, but only acquire a valid state once they have
	** been bound.
	** Zero is a reserved buffer object name and is never returned as a buffer
	** object by glGenBuffers().
	*/
	static void GenBuffers(const GLuint count, GLuint * arrs) {
		glGenBuffers(count, arrs);
	}


	static void DeleteBuffers(const GLuint count, GLuint * arrs) {
		glDeleteBuffers(count, arrs);
	}

	/*
	** Specifies the current active buffer object. target must be set to one of
	** GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER,
	** GL_PIXEL_PACK_BUFFER, GL_PIXEL_UNPACK_BUFFER,
	** GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER,
	** GL_TRANSFORM_FEEDBACK_BUFFER, or GL_UNIFORM_BUFFER. buffer
	** specifies the buffer object to be bound to.
	** glBindBuffer() does three things: 1. When using buffer of an unsigned
	** integer other than zero for the first time, a new buffer object is created
	** and assigned that name. 2. When binding to a previously created buffer
	** object, that buffer object becomes the active buffer object. 3. When
	** binding to a buffer value of zero, OpenGL stops using buffer objects for
	** that target.
	*/
	static void BindBuffers(const BufferType bufferType, const GLuint buffer) {
		glBindBuffer(bufferType, buffer);
	}

	/*
	** Returns GL_TRUE if buffer is the name of a buffer object that has been
	** bound, but has not been subsequently deleted. Returns GL_FALSE if
	** buffer is zero or if buffer is a nonzero value that is not the name of a buffer
	** object.
	*/
	static bool IsBuffer(const GLuint index) {
		return glIsBuffer(index) == GL_TRUE;
	}

	/*
	>>> Allocates memoty EVEN IF DATA POINTER IS NULL
	Allocates bytesToAlloc storage units (usually BYTES) of OpenGL server memory for
	storing data or indices. Any previous data associated with the currently
	bound object will be deleted.
	bytesToAlloc - is the amount of storage required for storing the respective data. This
	value is generally number of elements in the data multiplied by their
	respective storage size.
	data is either a pointer to a client memory that is used to initialize the
	buffer object or NULL. If a valid pointer is passed, size units of storage are
	copied from the client to the server. If NULL is passed, size units of
	storage are reserved for use but are left uninitialized.
	usage provides a hint as to how the data will be read and written after
	allocation. Valid values are GL_STREAM_DRAW, GL_STREAM_READ,
	GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ,
	GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ,
	GL_DYNAMIC_COPY.
	*/
	static void FillBufferWithData(const BufferType bufferType,
		const GLsizeiptr bytesToAlloc,
		const GLvoid *data,
		const UsageType usage)
	{
		glBufferData(bufferType, bytesToAlloc, data, usage);
	}

	// replaces part of the data in buffer
	static void FillBufferPart(const BufferType bufferType,
		const GLsizeiptr offset,
		const GLsizeiptr bytesToReplace,
		const GLvoid *data)
	{
		glBufferSubData(bufferType, offset, bytesToReplace, data);
	}

	static void ClearBufferWithData(const BufferType bufferType,
		const GLenum internalFormat,
		const GLenum format,
		const GLenum type,
		const GLvoid *data)
	{
		glClearBufferData(bufferType, internalFormat, format, type, data);
	}

	static void ClearBufferPartWithData()
	{
		//glBufferSubData(...)
	}

	/*
	Copies part of the data store of the buffer object bound to readtarget into
	the data store of the buffer object bound to writetarget. The bytesToCopy bytes of
	data at readoffset within readtarget are copied into writetarget at writeoffset.
	If readoffset or writeoffset together with size would cause either OpenGL to
	access any area outside the bound buffer objects, a GL_INVALID_VALUE
	error is generated.
	*/
	static void CopyBufferSubData(const BufferType readTarget,  // GL_COPY_READ_BUFFER?
		const BufferType writeTarget, // GL_COPY_WRITE_BUFFER?
		const int readOffset,
		const int writeOffset,
		const unsigned int bytesToCopy)
	{
		glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, bytesToCopy);
	}

	/*
	Returns some or all of the data from the buffer object currently bound
	to target. Data starting at byte-offset offset and extending for size bytes is
	copied from the data store to the memory pointed to by data. An error is
	thrown if the buffer object is currently mapped, or if offset and size together
	define a range beyond the bounds of the buffer object’s data store.
	*/
	static void GetBufferDataPart(const BufferType bufferType,
		const int offset,
		const unsigned int bytesToGet,
		GLvoid *data)
	{
		glGetBufferSubData(bufferType, offset, bytesToGet, data);
	}

	/*
	Maps to the client’s address space the entire data store of the buffer object
	currently bound to target. The data can then be directly read or written
	relative to the returned pointer, depending on the specified access policy.
	If OpenGL is unable to map the buffer object’s data store, glMapBuffer()
	generates an error and returns NULL. This may occur for system-specific
	reasons, such as low virtual memory availability.
	*/
	static void * MapBuffer(const BufferType bufferType, const BufferAccessType accessType)
	{
		return glMapBuffer(bufferType, accessType);
	}

	static bool UnmapBuffer(const BufferType bufferType)
	{
		return glUnmapBuffer(bufferType) == GL_TRUE;
	}

	// bitmask is MapBufferAccessBits enum
	static void * MapBufferRange(const BufferType bufferType,
		const GLintptr offset,
		const unsigned int lengthInBytes,
		const int accessBitMask)
	{
		return glMapBufferRange(bufferType, offset, lengthInBytes, accessBitMask);
	}

	/*
	** Used with GL_ARRAY_BUFFER
	** Binds shader location variable to buffer?
	** location - variable location in shader (location == 0 etc)
	** components - a number of components to be updated per vertex (r, rg, rgb, rgba, bgra)
	** dataType - data type of each element in the array
	** shouldBeNormalized - obvious
	** byteOffsetBetweenElements - is the byte offset between consecutive elements in the array
	** offsetFromBufferStartInBytes - is the offset from the start of the buffer object in bytes for the first set of values in the array
	*/
	static void VertexAttribPointer(const GLuint			location,
		const ColorComponents	components,
		const DataType			dataType,
		const GLboolean			shouldBeNormalized,
		const GLsizei			byteOffsetBetweenElements,
		const GLuint			offsetFromBufferStartInBytes)
	{
		glVertexAttribPointer(location, components, dataType, shouldBeNormalized, byteOffsetBetweenElements, BUFFER_OFFSET(offsetFromBufferStartInBytes));
	}

	/*
	** Specifies that the vertex array associated with variable location is enabled
	*/
	static void EnableVertexAttribPointer(const GLuint location) {
		glEnableVertexAttribArray(location);
	}

	/*
	** Specifies that the vertex array associated with variable location is disabled
	*/
	static void DisableVertexAttribPointer(const GLuint location) {
		glDisableVertexAttribArray(location);
	}


	static void ClearBuffer(const ClearBufferType bufferType) {
		glClear(bufferType);
	}

	static void ClearBuffers(const GLbitfield bufferTypes) {
		glClear(bufferTypes);
	}


	static void Flush() {
		glFlush();
	}

	static void SetClearColor(const Color & color) {
		glClearColor(color.R(), color.G(), color.B(), color.A());
	}

	/*
	** Constructs a sequence of geometric primitives using the elements from
	** the currently bound vertex array starting at first and ending at
	** first + count ? 1. mode specifies what kinds of primitives are constructed
	** and is one of GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP,
	** GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, and
	** GL_PATCHES.
	*/
	static void DrawArrays(const DrawMode mode, const GLint first, const GLsizei count) {
		glDrawArrays(mode, first, count);
	}


	static void Enable(const Capability c) {
		glEnable(c);
	}

	static void Disable(const Capability c) {
		glDisable(c);
	}

	static GLboolean IsEnables(const Capability c) {
		return glIsEnabled(c);
	}

	/*
	** Returns the index of the uniform variable name associated with the
	** shader program. name is a null-terminated character string with no spaces.
	** A value of minus one (?1) is returned if name does not correspond to a
	** uniform variable in the active shader program, or if a reserved shader
	** variable name (those starting with gl_ prefix) is specified.
	** name can be a single variable name, an element of an array (by including
	** the appropriate index in brackets with the name), or a field of a structure
	** (by specifying name, then ‘‘.’’ followed by the field name, as you would in
	** the shader program). For arrays of uniform variables, the index of the
	** first element of the array may be queried either by specifying only the
	** array name (for example, ‘‘arrayName’’), or by specifying the index to the
	** first element of the array (as in ‘‘arrayName[0]’’).
	** The returned value will not change unless the shader program is relinked
	** (see glLinkProgram()).
	*/
	static GLuint GetUniformVarLocation(const GLuint glProgram, const std::string & var_name) {
		return glGetUniformLocation(glProgram, var_name.c_str());
	}

	/*
	** Called after linkProgram()
	** Returns the index of the named uniform block specified by
	** uniformBlockName associated with program. If uniformBlockName is not a
	** valid uniform block of program, GL_INVALID_INDEX is returned.
	*/
	static GLuint GetUniformBlockIndex(const GLuint shaderProgram, const char* uniformBlockName) {
		return glGetUniformBlockIndex(shaderProgram, uniformBlockName);
	}

	/*
	** targetBuffer - UniformBuffer or TransformFeedbaclBuffer
	** uniformBlockIndex - index of the uniform block - from GetUniformBlockIndex()
	** bufferIndex - index of the buffer object - from GenBuffers()
	** offset and size should be multiple of 4
	*/
	static void BindBufferRange(const BufferType targetBuffer,
		const GLuint uniformBlockIndex,
		const GLuint bufferIndex,
		const GLuint offsetInBytes,
		const GLuint bufferSizeToBind)
	{
		glBindBufferRange(targetBuffer, uniformBlockIndex, bufferIndex, offsetInBytes, bufferSizeToBind);
	}

	// Identical to BindBufferRange() with offset == 0 and size == buffer object size (all buffer)
	static void BindBufferBase(const BufferType targetBuffer,
		const GLuint uniformBlockIndex,
		const GLuint bufferIndex)
	{
		glBindBufferBase(targetBuffer, uniformBlockIndex, bufferIndex);
	}

	// explicitly set uniform block index(useful if multiple programs share the same uniform block)
	// Call BEFORE linkProgram()
	static void UniformBlockBinding(const GLuint glProgram, const GLuint blockIndexToAssign, const GLuint uniformBlockBinding) {
		glUniformBlockBinding(glProgram, blockIndexToAssign, uniformBlockBinding);
	}

	/*
	** Returns the indices associated with the uniformCount uniform variables
	** specified by name in the array uniformNames in the array uniformIndices
	** for program. Each name in uniformNames is assumed to be NULL
	** terminated, and both uniformNames and uniformIndices have
	** uniformCount elements in each array. If a name listed in uniformNames is
	** not the name of an active uniform variables, the value
	** GL_INVALID_INDEX is returned in the corresponding element in
	** uniformIndices.
	*/
	static void GetUniformIndices(const GLuint glProgram,
		const GLsizei variableCount,
		const char ** variableNames,
		GLuint * indexReturnArray)
	{
		glGetUniformIndices(glProgram, variableCount, variableNames, indexReturnArray);
	}

	// Allocates a shader object
	// returns 0 if error occured
	static GLuint CreateShaderObject(const ShaderType & shaderType) {
		return glCreateShader(shaderType);
	}

	static void DeleteShaderObject(const GLuint shaderObject) {
		glDeleteShader(shaderObject);
	}

	static void AddShaderSource(const GLuint shader, const std::string & shaderSource /*, const std::string * parts*/) {

		/*	GLchar ** partsStr = new GLchar*[partCount];
		GLint * lengths = new GLint[partCount];

		for (int i = 0; i < partCount; ++i) {
		partsStr[i] = const_cast<GLchar*>(parts[i].c_str());
		lengths[i] = parts[i].length();
		}
		const GLchar** ptr = partsStr;

		glShaderSource(shader, partCount, ptr, lengths);*/

		/*std::string v = "#version 140\n";
		std::string c = "//some common shader functions";
		std::string s = shaderSource;*/

		/*GLchar const* files[] = { v.c_str(), c.c_str(), s.c_str() };
		GLint lengths[] = { (GLint)v.size(),  (GLint)c.size(),  (GLint)s.size() };

		glShaderSource(shader, 3, files, lengths);*/
		const char* str = shaderSource.c_str();

		glShaderSource(shader, 1, &str, NULL);
	}

	static void CompileShaderObject(const GLuint shader) {
		glCompileShader(shader);
	}

	static void GetShaderObjectInfo(const GLuint shader, const ShaderInfoType infoType, GLint * param) {
		glGetShaderiv(shader, infoType, param);
	}

	static void GetShaderProgramInfo(const GLuint shaderProgram, const ShaderProgramInfoType infoType, GLint * param) {
		glGetProgramiv(shaderProgram, infoType, param);
	}

	static bool IsShader(const GLuint shaderObj) {
		return glIsShader(shaderObj) == GL_TRUE;
	}

	static std::string GetShaderObjectInfoLog(const GLuint shader) {
		GLint logLength = 0;
		GetShaderObjectInfo(shader, ShaderInfoType::SHADER_INFO_LOG_LENGTH, &logLength);

		char * log = new char[logLength + 1]; // not sure about 1 but extra cant be harmful

		glGetShaderInfoLog(shader, logLength, nullptr, log);

		std::string result = std::string(log);
		delete[] log;

		return result;
	}

	static std::string GetShaderProgramInfoLog(const GLuint shadeProgram) {
		GLint logLength = 0;
		GetShaderProgramInfo(shadeProgram, ShaderProgramInfoType::PROGRAM_INFO_LOG_LENGTH, &logLength);

		char * log = new char[logLength + 1]; // not sure about 1 but extra cant be harmful

		glGetProgramInfoLog(shadeProgram, logLength, nullptr, log);

		std::string result = std::string(log);
		delete[] log;

		return result;
	}

	static GLuint CreateShaderProgram() {
		return glCreateProgram();
	}

	static void DeleteProgram(const GLuint shaderProgram) {
		glDeleteProgram(shaderProgram);
	}

	static void AttachShaderToProgram(const GLuint shaderObject, const GLuint shaderProgram) {
		glAttachShader(shaderProgram, shaderObject);
	}

	static void DetachShaderFromProgram(const GLuint shaderObject, const GLuint shaderProgram) {
		glDetachShader(shaderProgram, shaderObject);
	}

	static void LinkShaderProgram(const GLuint shaderProgram) {
		glLinkProgram(shaderProgram);
	}

	static bool IsShaderProgram(const GLuint shaderProgram) {
		return glIsProgram(shaderProgram) == GL_TRUE;
	}

	static void UseShaderProgram(const GLuint shaderProgram) {
		glUseProgram(shaderProgram);
	}

	static void SetPointSize(const GLfloat size) {
		glPointSize(size);
	}

	static void SetLineWidth(const GLfloat width) {
		glLineWidth(width);
	}

	static void SetPolygonMode(const PolygonFace face, const PolygonMode mode) {
		glPolygonMode(face, mode);
	}

	/*
	** Controls how front-facing polygons are determined. By default, mode is
	** GL_CCW, which corresponds to a counterclockwise orientation of the
	** ordered vertices of a projected polygon in window coordinates. If mode is
	** GL_CW, faces with a clockwise orientation are considered front-facing.
	*/
	static void SetFrontFaceMode(const FrontFacePolygonMode mode) {
		glFrontFace(mode);
	}

	/*
	** Indicates which polygons should be discarded (culled) before they’re
	** converted to screen coordinates. The mode is either GL_FRONT,
	** GL_BACK, or GL_FRONT_AND_BACK to indicate front-facing,
	** back-facing, or all polygons. To take effect, culling must be enabled using
	** glEnable() with GL_CULL_FACE; it can be disabled with glDisable() and
	** the same argument.
	*/
	static void SetCullFace(const CullMode mode) {
		glCullFace(mode);
	}



};

