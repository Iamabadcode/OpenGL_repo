#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "GL_util.h"


Renderer::Renderer(vec2ui dimentions, const char* name)
	: m_window_ptr(openWindow(dimentions, name))
{
	
	glfwMakeContextCurrent(m_window_ptr);
	glewInit();
	
	GLCall(glViewport(0,0,dimentions.v0, dimentions.v1));
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

}

Renderer::Renderer(const char* name)
	: m_window_ptr(openFullScreenWindow(name))
{
	glfwMakeContextCurrent(m_window_ptr);
	glewInit();
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
}

Renderer::~Renderer()
{
	closeWindow(m_window_ptr);
}

void Renderer::SetKeyCallbackFn(void (*callback)(GLFWwindow*, int, int, int, int)) const
{
	glfwSetKeyCallback(m_window_ptr, callback);
}

bool Renderer::KeyState(const char key)
{
	switch (key) {
	case 'w':
		return glfwGetKey(m_window_ptr, GLFW_KEY_W) == GLFW_PRESS;
	case 'a':
		return glfwGetKey(m_window_ptr, GLFW_KEY_A) == GLFW_PRESS;
	case 's':
		return glfwGetKey(m_window_ptr, GLFW_KEY_S) == GLFW_PRESS;
	case 'd':
		return glfwGetKey(m_window_ptr, GLFW_KEY_D) == GLFW_PRESS;
	case ' ':
		return glfwGetKey(m_window_ptr, GLFW_KEY_SPACE) == GLFW_PRESS;
	}

	return false;
}

void Renderer::bufferSwap() const
{
	glfwSwapBuffers(m_window_ptr);

}

void Renderer::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

bool Renderer::shouldClose() const
{
	return glfwWindowShouldClose(m_window_ptr);
}

void Renderer::pollEvents() const
{
	glfwPollEvents();
}

GLFWwindow* Renderer::openWindow(vec2ui dimentions, const char* name) const
{
	GLFWwindow* window;
	if (!glfwInit()) { Debug::Log("GFLW initialization failiure"); ASSERT(false); }

	window = glfwCreateWindow(dimentions.v0, dimentions.v1, name, nullptr, nullptr);
	if (!window) { Debug::Log("GFLW window creation failiure"); glfwDestroyWindow(window); glfwTerminate(); ASSERT(false); }
	return window;
}

GLFWwindow* Renderer::openFullScreenWindow(const char* name) const 
{
	GLFWwindow* window;
	if (!glfwInit()) { Debug::Log("GFLW initialization failiure"); ASSERT(false); }

	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	if (!primaryMonitor) { glfwTerminate(); Debug::Log("GFLW failed to detect screen dimentions"); ASSERT(false); }

	const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
	if (!videoMode) { glfwTerminate(); Debug::Log("GFLW failed to get video mode for primary monitor"); ASSERT(false); }

	window = glfwCreateWindow(
		videoMode->width, videoMode->height,
		name,
		primaryMonitor,
		nullptr
	);
	if (!window) { Debug::Log("GFLW window creation failiure"); glfwDestroyWindow(window); glfwTerminate(); ASSERT(false); }

	return window;
}

void Renderer::closeWindow(GLFWwindow* window) const
{
	glfwDestroyWindow(window);
	glfwTerminate();
	Debug::Log("Released window", Debug::INFO);
}
