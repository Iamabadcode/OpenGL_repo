#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 texpos;

out vec3 vColor;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    texCoords = texpos;
    vColor = aColor;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
