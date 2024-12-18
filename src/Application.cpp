#include <iostream>

#include <GL/glew.h>

#include "Graphics/Window.h"
#include "util/Debug.h"
#include "Graphics/Renderer.h"
#include "Graphics/ElementBuffer.h"

int main()
{
	Debug::activate();
		
	Renderer renderer({1000, 500}, "OpenGL Window");

	float verticies[] = {
		-0.5,-0.5,
		0.5, -0.5,
		0.5, 0.5,
		-0.5, 0.5
	};
	unsigned int indicies[] = {
		0,1,2,
		2,3,0
	};

	AttribedVertexBuffer element_buffer(Layout({{GL_FLOAT, 2, false}}), (void*)verticies, sizeof(verticies), GL_STATIC_DRAW);


	unsigned int index_buffer;
	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	while(true)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(element_buffer.m_vertex_array);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(renderer.window.ptr());

	}
	glDeleteVertexArrays(1, &element_buffer.m_vertex_array);
	
	glDeleteBuffers(1, &index_buffer);
}