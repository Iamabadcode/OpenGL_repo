#pragma once
#include <GL/glew.h>
#include "../util/Debug.h"

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
	}
	ASSERT(false);
	return 0;
}