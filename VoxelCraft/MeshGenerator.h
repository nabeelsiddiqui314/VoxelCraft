#pragma once
#include "Mesh.h"
#include "ChunkBlocks.h"

class MeshGenerator
{
public:
	void generateMesh(std::int16_t originX, std::int16_t originZ, const ChunkBlocks& chunk, 
		const ChunkBlocks& cFront, const ChunkBlocks& cBack, const ChunkBlocks& cLeft, 
		const ChunkBlocks& cRight);
	const Mesh& getMesh() const;
	void cleanUp();
private:
	void addFace(std::int16_t x, std::int16_t y, std::int16_t z, const std::array<GLfloat, 12>& face);
private:
	Mesh m_mesh;
	GLuint m_index = 0;

	static const std::array<GLfloat, 12> s_front;
	static const std::array<GLfloat, 12> s_back;
	static const std::array<GLfloat, 12> s_right;
	static const std::array<GLfloat, 12> s_left;
	static const std::array<GLfloat, 12> s_top;
	static const std::array<GLfloat, 12> s_bottom;
};

