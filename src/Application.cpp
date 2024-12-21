#include <iostream>
#include "Graphics/Renderer.h"


int main()
{
	Debug::activate();
	Renderer renderer({1000, 500}, "OpenGL Window");

	while(!glfwWindowShouldClose(renderer.window.ptr()))
	{	
		glClear(GL_COLOR_BUFFER_BIT);
	

		if (GLenum e = glGetError()) std::cout << "ErrorCode: " << e<< std::endl;
		glfwSwapBuffers(renderer.window.ptr());
		glfwPollEvents();
	}
}