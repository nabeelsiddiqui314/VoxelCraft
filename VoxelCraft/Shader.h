#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader() = default;
	Shader(const char* vertexPath, const char* fragmentPath);
public:
	void loadShader(const char* vertexPath, const char* fragmentPath);
	void useProgram();
	void loadMVP(const glm::mat4& mat4) const;
private:
	GLuint m_program;
	std::string m_vertexCode, m_fragmentCode;
};

