#pragma once
#include <array>
#include <GL/glew.h>

struct Mesh;

class SegmentMesh
{
public:
	SegmentMesh(Mesh& mesh);
	void addFace(std::int16_t x, std::int16_t y, std::int16_t z, int textureIndex, const std::array<GLfloat, 12>& face, GLfloat natLight, GLfloat skyExposure);
private:
	Mesh& m_mesh;
	GLuint m_index = 0;
};

