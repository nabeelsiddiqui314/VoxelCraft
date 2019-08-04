#include "stdafx.h"
#include "Shader.h"
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	loadShader(vertexPath, fragmentPath);
}

void Shader::loadShader(const char* vertexPath, const char* fragmentPath) {
	std::string	vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_READING_UNSUCCESSFUL" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::useProgram() {
	glUseProgram(m_program);
}

void Shader::setUniform1i(const std::string& name, int val) const {
	glUniform1i(getUniformLocation(name), val);
}

GLint Shader::getUniformLocation(const std::string& name) const {
	if (m_uniformHashMap.find(name) != m_uniformHashMap.end())
		return m_uniformHashMap.at(name);
	return glGetUniformLocation(m_program, name.c_str());
}

void Shader::setUniformMat4(const std::string& name, const glm::mat4& val) const {
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &val[0][0]);
}