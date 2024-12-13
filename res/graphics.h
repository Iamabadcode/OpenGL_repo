#pragma once
#include <string>
#include <vector>

class Shader {
public:
    std::string name;
    char* program;
    int length;
    unsigned int type;
    unsigned int id;

    Shader(std::string name, unsigned int shader_type);
    ~Shader();
    void loadShaderProgram(std::string name);
    void compile();
    

};

class Screen {
private:
    int size_x;
    int size_y;
    GLFWwindow* win_p = nullptr;
    unsigned int program_id;

public:

	Screen(int, int);

    void CreateShaderProgram(std::vector<std::pair<std::string, unsigned int>> shaders);
    
	GLFWwindow* window_p();

    ~Screen();
};