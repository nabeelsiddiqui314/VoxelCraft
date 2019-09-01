#pragma once
#include "Mesh.h"
#include <array>

class MeshGenerator
{
public:
	void addFace(std::int16_t x, std::int16_t y, std::int16_t z, const std::array<GLfloat, 12>& face);
	void cleanUp();
	const Mesh& getMesh() const;
private:
	Mesh m_mesh;
	GLuint m_index = 0;
};

