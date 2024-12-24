#version 330 core

in vec3 vColor; // Color from vertex shader
out vec4 FragColor;

void main()
{
    FragColor = vec4(vColor, 1.0); // Output the color
}
