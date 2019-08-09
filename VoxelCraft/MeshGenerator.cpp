#include "stdafx.h"
#include "MeshGenerator.h"

// indices in 0, 1, 2, 0, 2, 3

const std::vector<GLfloat> MeshGenerator::s_front = {
	0, 0, 0,
	1, 0, 0,
	1, 1, 0,
	0, 1, 0
};

const std::vector<GLfloat> MeshGenerator::s_back = {
	0, 1, -1,
	1, 1, -1,
	1, 0, -1,
	0, 0, -1
};

const std::vector<GLfloat> MeshGenerator::s_left = {
	0, 0, -1,
	0, 0,  0,
	0, 1,  0,
	0, 1, -1
};

const std::vector<GLfloat> MeshGenerator::s_right = {
	1, 0, -1,
	1, 0,  0,
	1, 1,  0,
	1, 1, -1
};

const std::vector<GLfloat> MeshGenerator::s_top = {
	0, 1,  0,
	1, 1,  0,
	1, 1, -1,
	0, 1, -1
};

const std::vector<GLfloat> MeshGenerator::s_bottom = {
	0, 0, -1,
	1, 0, -1,
	1, 0,  0,
	0, 0,  0
};

MeshGenerator::MeshGenerator(const ChunkManager* chunks)
: p_chunks(chunks) {}

Model MeshGenerator::generateMesh(const VecXZ& pos) {
	BlockType top
	, bottom
	, left
	, right
	, front
	, back;

	auto setNeighbors = [&](std::int16_t x, std::int16_t y, std::int16_t z) {
		// x
		if (x - 1 < 0)
			left = p_chunks->getBlock({pos.x - 1, pos.z}, CHUNK_WIDTH - 1, y, z);
		else
			left = p_chunks->getBlock(pos, x - 1, y, z);

		if (x + 1 >= CHUNK_WIDTH)
			right = p_chunks->getBlock({pos.x + 1, pos.z}, 0, y, z);
		else
			right = p_chunks->getBlock(pos, x + 1, y, z);

		//z

		if (z - 1 < 0)
			back = p_chunks->getBlock({ pos.x, pos.z - 1}, x, y, CHUNK_WIDTH - 1);
		else
			back = p_chunks->getBlock(pos, x, y, z - 1);

		if (z + 1 >= CHUNK_WIDTH)
			front = p_chunks->getBlock({ pos.x, pos.z + 1}, x, y, 0);
		else
			front = p_chunks->getBlock(pos, x, y, z + 1);

		// y
		if (y - 1 < 0)
			bottom = BlockType::VOID;
		else
			bottom = p_chunks->getBlock(pos, x, y - 1, z);

		if (y + 1 >= CHUNK_HEIGHT)
			top = BlockType::VOID;
		else
			top = p_chunks->getBlock(pos, x, y + 1, z);
	};

	for (std::int16_t x = 0; x < CHUNK_WIDTH; x++) {
		for (std::int16_t y = 0; y < CHUNK_HEIGHT; y++) {
			for (std::int16_t z = 0; z < CHUNK_WIDTH; z++) {
				if (p_chunks->getBlock(pos, x, y, z) == BlockType::VOID)
					continue;
				setNeighbors(x, y, z);
				if (top == BlockType::VOID)
					addFace(pos, x, y, z, s_top);
				if (bottom == BlockType::VOID)
					addFace(pos, x, y, z, s_bottom);
				if (left == BlockType::VOID)
					addFace(pos, x, y, z, s_left);
				if (right == BlockType::VOID)
					addFace(pos, x, y, z, s_right);
				if (front == BlockType::VOID)
					addFace(pos, x, y, z, s_front);
				if (back == BlockType::VOID)
					addFace(pos, x, y, z, s_back);
			}
		}
	}
	Model model;
	model.addMesh(m_mesh);
	return model;
}

void MeshGenerator::addFace(const VecXZ& pos, std::int16_t x, std::int16_t y, std::int16_t z, const std::vector<GLfloat>& face) {
	m_mesh.textureCoords.insert(m_mesh.textureCoords.end(),  {
			0, 0,
			1, 0,
			1, 1,
			0, 1
		} );

	m_mesh.indices.insert(m_mesh.indices.end(), {
			m_index,
			m_index + 1,
			m_index + 2,
			m_index,
			m_index + 2,
			m_index + 3
		});
	m_index += 4;

	int faceIndex = 0;
	for (int i = 0; i < 4; i++) {
		m_mesh.vertices.push_back(pos.x * CHUNK_WIDTH + x + face[faceIndex++]);
		m_mesh.vertices.push_back(y + face[faceIndex++]);
		m_mesh.vertices.push_back(pos.z * CHUNK_WIDTH + z + face[faceIndex++]);
	}
}
