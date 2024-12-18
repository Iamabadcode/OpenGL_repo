#pragma once

#include <GLFW/glfw3.h>

#include "../util/math.h"

class GLFW_window
{
private:
	GLFWwindow* m_Window;

public:
	GLFW_window(vec2ui, const char*);
	GLFW_window(const char*);
	~GLFW_window();

	GLFWwindow* ptr();
};