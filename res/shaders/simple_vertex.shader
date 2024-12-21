#version 330 core

layout(location = 0) in vec2 position;

void main(){

    gl_Position = vec4(position, vec2(1.0,1.0)); 
    
}