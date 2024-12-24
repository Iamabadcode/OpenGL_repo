#version 330 core

in vec3 vColor; // Color from vertex shader
in vec2 texCoords;
out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, texCoords); // Output the color
}
