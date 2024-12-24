#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../util/Debug.h"
#include "../util/math.h"

#define GLCall(x)\
	{while(glGetError()){} x;\
	while(GLuint error = glGetError())\
		{ Debug::Log("[OpenGL ERROR] : (" + std::to_string(error) + ") : " + std::string(__FILE__) + " l" + std::to_string(__LINE__) + " : " + #x);ASSERT(false); }}


inline unsigned int GetGlTypeSize(unsigned int GL_Type)
{
	switch (GL_Type)
	{
	case GL_FLOAT:
		return sizeof(GLfloat);
	case GL_INT:
		return sizeof(GLint);
	case GL_UNSIGNED_INT:
		return sizeof(GLuint);
	case GL_BYTE:
		return sizeof(GLbyte);
	case GL_UNSIGNED_BYTE:
		return sizeof(GLubyte);
	case GL_DOUBLE:
		return sizeof(GLdouble);
	}
	ASSERT(false);
	return 0;
}