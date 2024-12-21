#pragma once
#include <string>
#include <vector>

class ShaderProgram
{
public:
	ShaderProgram(std::vector<std::pair<const char*, unsigned int >> filename_and_gl_type);
	~ShaderProgram();

	void Use() const { glUseProgram(m_program_id); }
	unsigned int id() const { return m_program_id; }
	
private:
	unsigned int m_program_id;
	
	unsigned int compileShader(const char* code, unsigned int shader_type);
	std::string getProgramFromFile(const char* name);

};