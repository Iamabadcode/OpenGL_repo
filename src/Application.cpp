#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../res/graphics.h"


int main(void)
{
    Screen::initialize(500, 1000);
    
    Screen::includeShaders({
        { "simple_vertex", GL_VERTEX_SHADER},
        {"simple_fragment", GL_FRAGMENT_SHADER}
    });

    Screen::initArrayBuffer();

    float positions[] = {
        -0.5, -0.5,
        0.5, -0.5,
        0.5, 0.5,
    };
    
    Screen::saveVerticies(positions, 3);

    // index, size, type, normalized, stride, pointer
    

    /* Loop until the user closes the window */
    while (Screen::Open())
    {

        Screen::render();

        glfwPollEvents();
    }
    Screen::release();
    return 0;
}