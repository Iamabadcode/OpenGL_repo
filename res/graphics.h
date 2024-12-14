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
    void loadShaderProgram(std::string name);
    void compile();    

};

class Screen {
private:
    static int size_x;
    static int size_y;
    static GLFWwindow* win_p;
    static unsigned int program_id;
    static unsigned int VAO;
    static unsigned int VBO;
    static int vert_count;
    enum ConstVals {
        A_BUFFER_VERT_SIZE = 2 * sizeof(float)
    };
public:
    
    static void initialize(int, int);
    static void includeShaders(std::vector<std::pair<std::string, unsigned int>> shaders);
    static void initArrayBuffer();
    static void saveVerticies(float*, int);
    static void render();

	static GLFWwindow* window_p();
    static bool Open();
    
    static void release();
};