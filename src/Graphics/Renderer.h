#pragma once

#include <GL/glew.h>

#include "Window.h"
#include "../util/Debug.h"
#include "../util/math.h"


class Renderer
{
private:
public:
	Renderer(vec2ui, const char* name);
	Renderer(const char* name);
	~Renderer();

	GLFW_window window;

};

