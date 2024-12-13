#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <stdexcept>
#include <cstdlib>

#include "../res/graphics.h"

Shader::Shader(std::string _name, unsigned int shader_type) : type(shader_type), name(_name) {
    loadShaderProgram(_name);
    compile();
}

void Shader::loadShaderProgram(std::string name) {
    // Open the file for reading
    std::string path = "res/shaders/" + name + ".shader";
    HANDLE fileHandle = CreateFileA(path.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Failed to open file");
    }
    size_t fileSize;
    // Get the file size
    fileSize = GetFileSize(fileHandle, NULL);
    if (fileSize == INVALID_FILE_SIZE) {
        CloseHandle(fileHandle);
        throw std::runtime_error("Failed to get file size");
    }

    // Create a file mapping object
    HANDLE fileMapping = CreateFileMapping(fileHandle, NULL, PAGE_READONLY, 0, fileSize, NULL);
    if (fileMapping == NULL) {
        CloseHandle(fileHandle);
        throw std::runtime_error("Failed to create file mapping");
    }

    // Map the file into memory
    program = static_cast<char*>(MapViewOfFile(fileMapping, FILE_MAP_READ, 0, 0, fileSize));
    if (program == NULL) {
        CloseHandle(fileMapping);
        CloseHandle(fileHandle);
        throw std::runtime_error("Failed to map view of file");
    }

    // Clean up the handles as they are no longer needed after mapping
    CloseHandle(fileMapping);
    CloseHandle(fileHandle);
}

void Shader::compile() {
    id = glCreateShader(type);
    glShaderSource(id, 1, &program, NULL);
    glCompileShader(id);
    GLint vertex_compiled;
    glGetShaderiv(id, GL_COMPILE_STATUS, &vertex_compiled);
    if (vertex_compiled != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(id, 1024, &log_length, message);
        std::cout << "Shader " + name + " failed to compile:\n" <<  message << std::endl;
    }
    std::cout << program[0];
    delete[] program;
}

Shader::~Shader(){
    glDeleteShader(id);
}

Screen::Screen(int x_size, int y_size) : size_x(x_size), size_y(y_size), win_p(nullptr) {
    //Window:
    if (!glfwInit()) {
        std::cerr << "Error: GLFW failed to initialize." << std::endl;
        return;
    }
    win_p = glfwCreateWindow(size_x, size_y, "OpenGL", nullptr, nullptr);
    if (!win_p) {
        std::cerr << "Error: Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(win_p);
    //load OpenGL:
    if (glewInit() != GLEW_OK) {
        std::cout << "ERROR in initializaition of glew" << std::endl;
    }
    std::cout << "Using OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(0.12, 0.5, 0.3, 1.0);
    glViewport(0, 0, size_x, size_y);
}

void Screen::CreateShaderProgram(std::vector<std::pair<std::string, unsigned int>> shaders) {
    program_id = glCreateProgram();
    for (int i = 0; i < shaders.size(); i++) {
        Shader shader(shaders[i].first, shaders[i].second);
        glAttachShader(program_id, shader.id);
    }
    glLinkProgram(program_id);
}

GLFWwindow* Screen::window_p() {
    return win_p;
}

Screen::~Screen() {
    if (win_p) {
        glfwDestroyWindow(win_p);
    }
    glfwTerminate();
    std::cout << "Window resources released." << std::endl;
}