#pragma once
#include "ChunkManager.h"
#include "Model.h"

class MeshGenerator
{
public:
	MeshGenerator(const ChunkManager* chunks);
public:
	Model generateMesh(const VecXZ& pos);
private:
	void addFace(const VecXZ& pos, std::int16_t x, std::int16_t y, std::int16_t z, const std::vector<GLfloat>& face);
private:
	const ChunkManager* p_chunks;
	Mesh m_mesh;
	GLuint m_index = 0;

	static const std::vector<GLfloat> s_front;
	static const std::vector<GLfloat> s_back;
	static const std::vector<GLfloat> s_right;
	static const std::vector<GLfloat> s_left;
	static const std::vector<GLfloat> s_top;
	static const std::vector<GLfloat> s_bottom;
};

