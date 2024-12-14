#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <stdexcept>
#include <cstdlib>

#include "../res/graphics.h"

int Screen::size_x = 1000;
int Screen::size_y = 500;
GLFWwindow* Screen::win_p = nullptr;
unsigned int Screen::program_id = 0;
unsigned int Screen::VAO = 0;
unsigned int Screen::VBO = 0;
int Screen::vert_count = 0;


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
    if (program) {
        UnmapViewOfFile(program);
    }
}

void Screen::initialize(int x_size, int y_size) {
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

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glViewport(0, 0, size_x, size_y);
}

void Screen::includeShaders(std::vector<std::pair<std::string, unsigned int>> shaders) {
    program_id = glCreateProgram();
    std::vector<GLuint> shader_ids;
    for (int i = 0; i < shaders.size(); i++) {
        Shader shader(shaders[i].first, shaders[i].second);
        shader_ids.push_back(shader.id);
        glAttachShader(program_id, shader.id);
    }
    glLinkProgram(program_id);
    GLint success;
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program_id, 512, NULL, infoLog);
        throw std::runtime_error("Program linking failed: " + std::string(infoLog));
    }
    glUseProgram(program_id);

    for (int i = 0; i < shader_ids.size(); i++) {
        glDeleteShader(shader_ids[i]);
    }
}

void Screen::initArrayBuffer() {
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);
}

void Screen::saveVerticies(float* data, int vertex_count) {
    
    glBufferData(GL_ARRAY_BUFFER, vertex_count * A_BUFFER_VERT_SIZE, data, GL_STATIC_DRAW);
    vert_count = vertex_count;
}

void Screen::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, vert_count);

    glfwSwapBuffers(win_p);
}

GLFWwindow* Screen::window_p() {
    return win_p;
}

bool Screen::Open() {
    return !glfwWindowShouldClose(win_p);
}

void Screen::release() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(program_id);
    if (win_p) {
        glfwDestroyWindow(win_p);
    }
    glfwTerminate();
    std::cout << "Window resources released." << std::endl;
}