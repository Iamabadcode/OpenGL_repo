#pragma once

#include <GL/glew.h>

#include "../util/math.h"
#include "../util/Debug.h"

#include "Window.h"
#include "ElementBuffer.h"
#include "StaticMesh.h"
#include "ShaderProgram.h"






class Renderer
{
private:
public:
	Renderer(vec2ui, const char* name);
	Renderer(const char* name);
	~Renderer();

	GLFW_window window;

};

