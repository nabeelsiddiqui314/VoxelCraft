#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <unordered_map>

class Shader
{
public:
	Shader() = default;
	Shader(const char* vertexPath, const char* fragmentPath);
public:
	void loadShader(const char* vertexPath, const char* fragmentPath);
	void useProgram();
	void setUniformMat4(const std::string& name, const glm::mat4& val) const;
	void setUniform1i(const std::string& name, int val) const;
	GLint getUniformLocation(const std::string& name) const;
private:
	GLuint m_program;
	std::string m_vertexCode, m_fragmentCode;
	std::unordered_map<std::string, GLint> m_uniformHashMap;
};

