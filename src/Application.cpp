#include <iostream>
#include "Graphics/Renderer.h"


int main()
{
	Debug::activate();
	Renderer renderer({1000, 500}, "OpenGL Window");

	ShaderProgram program1({
		{"shaders/simple_fragment.shader", GL_FRAGMENT_SHADER},
		{"shaders/simple_vertex.shader", GL_VERTEX_SHADER }
	});

	float verticies[] = {
		-0.5,-0.5,
		0.5, -0.5,
		0.5, 0.5,
		-0.5, 0.5,
		1.0, 1.0
	};
	
	StaticMesh mesh({ Attribute(GL_FLOAT, 2, false) }, verticies, 10 * sizeof(float));
	StaticMesh mesh2({ Attribute(GL_FLOAT, 2, false) }, verticies, 10 * sizeof(float));
	
	StaticMesh::LoadAllBuffers();
	unsigned int indicies[] = {
		0,1,2,
		2,3,1
	};
	unsigned int indicies2[] = {
		0,1,4
	};

	mesh.AddProgram(program1.id(), indicies, 6);
	mesh2.AddProgram(0, indicies2, 3);
	
	while(!glfwWindowShouldClose(renderer.window.ptr()))
	{	
		glClear(GL_COLOR_BUFFER_BIT);
		mesh2.DrawFullMesh();
		mesh.DrawFullMesh();

		if (GLenum e = glGetError()) std::cout << "ErrorCode: " << e<< std::endl;
		glfwSwapBuffers(renderer.window.ptr());
		glfwPollEvents();
	}
}