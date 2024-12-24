#include <iostream>
#include "Graphics/Renderer.h"


int main()
{
	Debug::activate();
	Renderer renderer( {800, 600}, "OpenGL window");
	
	float verticies[] = {
		-1.2, -1.2, 1.2, 1.0 ,0.0,0.0, 0.0, 0.0,
		1.2, -1.2, 1.2, 1.0, 0.0, 0.0, 1.0, 0.0,
		1.2, 1.2, 1.2, 0.0, 1.0, 0.0, 1.0, 1.0,
		-1.2, 1.2, 1.2, 0.0, 0.5, 0.0, 0.0, 1.0
	};
	StaticMesh plane({ {GL_FLOAT, 3, false}, {GL_FLOAT, 3, false} , { GL_FLOAT, 2, false} }, verticies, sizeof(verticies));
	ShaderProgram plastic_program({ { "shaders/3dShaderfrg.shader", GL_FRAGMENT_SHADER}, {"shaders/3dShadervtx.shader", GL_VERTEX_SHADER} });
	Texture texture("textures/wall.jpg");
	plastic_program.CoupleTexture(texture.id());
	unsigned int indicies[] = {
		0,1,2, 2,3,0
	};
	plane.AddProgram(plastic_program.id(), indicies, 6);
	// Define matrices as float arrays
	float model[16] = {
		1.0f, 0.0f, 0.0f, 0.0f, // Column 1
		0.0f, 1.0f, 0.0f, 0.0f, // Column 2
		0.0f, 0.0f, 1.0f, 0.0f, // Column 3
		0.0f, 0.0f, 0.0f, 1.0f  // Column 4
	};

	float view[16] = {
		1.0f, 0.0f, 0.0f, 0.0f,  // Column 1
		0.0f, 1.0f, 0.0f, 0.0f,  // Column 2
		0.0f, 0.0f, 1.0f, 0.0f,  // Column 3
		0.0f, 0.0f, -3.0f, 1.0f  // Column 4 (translate along Z-axis)
	};

	float projection[16] = {
		1.0f, 0.0f, 0.0f, 0.0f, // Column 1
		0.0f, 1.0f, 0.0f, 0.0f, // Column 2
		0.0f, 0.0f, -1.0f, -1.0f, // Column 3 (perspective projection)
		0.0f, 0.0f, -0.2f, 0.0f  // Column 4
	};

	// Use shader program
	plastic_program.Use();

	// Find uniform locations
	int modelLoc = glGetUniformLocation(plastic_program.id(), "model");
	int viewLoc = glGetUniformLocation(plastic_program.id(), "view");
	int projLoc = glGetUniformLocation(plastic_program.id(), "projection");

	// Set the uniforms
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection);


	bool running = true;
	while (!renderer.shouldClose() && running) {
		renderer.clear();
		StaticMesh::FastDraw();
		renderer.bufferSwap();
		renderer.pollEvents();
		if (renderer.KeyState('a')) running = false;
	}

}