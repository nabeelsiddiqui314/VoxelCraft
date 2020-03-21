#pragma once
#include <array>
#include <GL/glew.h>
#include "../../OGL/Core/Mesh.h"

class SegmentMesh
{
public:
	void addFace(std::int16_t x, std::int16_t y, std::int16_t z, int textureIndex, const std::array<GLfloat, 12>& face, GLfloat natLight, GLfloat skyExposure);

	void cleanUp();
	const Mesh& getMesh() const;
private:
	Mesh m_mesh;
	GLuint m_index = 0;
};

