#include "GL_util.h"
#include "ShaderProgram.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>


ShaderProgram::ShaderProgram(std::vector<std::pair<const char*, unsigned int>> shaders)
{
    std::vector<unsigned int> compiled_shaders;
    for (int i = 0; i < shaders.size(); i++)
    {
        std::string code = getProgramFromFile(shaders[i].first);
        unsigned int shader_id = compileShader(code.c_str(), shaders[i].second);
        compiled_shaders.push_back(shader_id);
    }
    m_program_id = glCreateProgram();
    for (int i = 0; i < compiled_shaders.size(); i++) 
    {
        GLCall(glAttachShader(m_program_id, compiled_shaders[i]));
    }
    glLinkProgram(m_program_id);
    GLint success;
    GLCall(glGetProgramiv(m_program_id, GL_LINK_STATUS, &success));
    if (!success) 
    {
        char infoLog[512];
        GLCall(glGetProgramInfoLog(m_program_id, 512, nullptr, infoLog));
        std::cerr << "ERROR: Shader Program Linking Failed\n" << infoLog << std::endl;
    }
    for (int i = 0; i < compiled_shaders.size(); i++) 
    {
        GLCall(glDeleteShader(compiled_shaders[i]));
    }
    Debug::Log("Created shader program", Debug::INFO);
}

ShaderProgram::~ShaderProgram()
{
    if (m_program_id);
    GLCall(glDeleteProgram(m_program_id));
    Debug::Log("Deleted shader program", Debug::INFO);
}

unsigned int ShaderProgram::compileShader(const char* source, unsigned int shader_type)
{
    GLuint shader = glCreateShader(shader_type);
    GLCall(glShaderSource(shader, 1, &source, nullptr));
    glCompileShader(shader);

    // Check for compilation errors
    GLint success;
    GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (!success) {
        char infoLog[512];
        GLCall(glGetShaderInfoLog(shader, 512, nullptr, infoLog));
        std::cerr << "ERROR: Shader Compilation Failed\n" << infoLog << std::endl;
        glfwTerminate();
        ASSERT(false); //shader failed to compile
    }

    return shader;
}

std::string ShaderProgram::getProgramFromFile(const char* name)
{
    std::ifstream file(std::string("res/") + name, std::ios::in); // Use std::ios::in for reading
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open shader file");
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    Debug::Log(std::string("Loaded ") + name, Debug::INFO);
    return buffer.str();
}

