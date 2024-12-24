#pragma once
#include <concepts>
#include "GL_util.h"
#include "ElementBuffer.h"
#include "StaticMesh.h"
#include "ShaderProgram.h"
#include "Texture.h"





class Renderer
{

public:
	Renderer(vec2ui, const char* name);
	Renderer(const char* name);
	~Renderer();

	void SetKeyCallbackFn(void (*callback)(GLFWwindow*, int, int, int, int)) const;
	bool KeyState(const char);

	void bufferSwap() const;
	void clear() const;
	bool shouldClose() const;
	void pollEvents() const;
private:
	GLFWwindow* m_window_ptr;

	GLFWwindow* openWindow(vec2ui, const char* name)	const;
	GLFWwindow* openFullScreenWindow(const char* name)	const;

	void closeWindow(GLFWwindow* window)	const;
};

