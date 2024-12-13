#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../res/graphics.h"

int main(void)
{
    Screen screen(1000, 500);
    /*
    screen.CreateShaderProgram({
        { "simple_vertex", GL_VERTEX_SHADER},
        /*{"simple_fragment", GL_FRAGMENT_SHADER}*/
    //});





    float positions[] = {
        -0.5, -0.5,
        0.5, -0.5,
        0.5, 0.5,
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(float), positions, GL_STATIC_DRAW);


    // index, size, type, normalized, stride, pointer
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(screen.window_p()))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(screen.window_p());

        /* Poll for and process events */
        glfwPollEvents();
    }
   
    return 0;
}