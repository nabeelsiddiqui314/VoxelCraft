#pragma once
#include <vector>
#include <GLFW/glfw3.h>

struct Mesh {
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> textureCoords;
	std::vector<GLuint> indices;
};