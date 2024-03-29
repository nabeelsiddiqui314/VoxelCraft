#pragma once
#include <vector>
#include <GL/glew.h>

struct Mesh {
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> textureCoords;
	std::vector<GLuint> indices;
	std::vector<GLfloat> naturalLight;
	std::vector<GLfloat> skyExposure;
};