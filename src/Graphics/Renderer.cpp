#include "Renderer.h"
#include "GL_util.h"

Renderer::Renderer(vec2ui dimentions, const char* name)
	: window(dimentions, name)
{
	
	glfwMakeContextCurrent(window.ptr());
	glewInit();
	
	GLCall(glViewport(0,0,dimentions.v0, dimentions.v1));
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

}

Renderer::Renderer(const char* name)
	: window(name)
{
	glfwMakeContextCurrent(window.ptr());
	glewInit();
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
}

Renderer::~Renderer()
{

}
