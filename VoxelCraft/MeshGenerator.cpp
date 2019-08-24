#include "stdafx.h"
#include "MeshGenerator.h"

// indices in 0, 1, 2, 0, 2, 3

const std::array<GLfloat, 12> MeshGenerator::s_front = {
	0, 0, 0,
	1, 0, 0,
	1, 1, 0,
	0, 1, 0
};

const std::array<GLfloat, 12> MeshGenerator::s_back = {
	1, 0, -1,
	0, 0, -1,
	0, 1, -1,
	1, 1, -1
};

const std::array<GLfloat, 12> MeshGenerator::s_left = {
	0, 0, -1,
	0, 0,  0,
	0, 1,  0,
	0, 1, -1
};

const std::array<GLfloat, 12> MeshGenerator::s_right = {
	1, 0,  0,
	1, 0, -1,
	1, 1, -1,
	1, 1,  0
};

const std::array<GLfloat, 12> MeshGenerator::s_top = {
	0, 1,  0,
	1, 1,  0,
	1, 1, -1,
	0, 1, -1
};

const std::array<GLfloat, 12> MeshGenerator::s_bottom = {
	0, 0, -1,
	1, 0, -1,
	1, 0,  0,
	0, 0,  0
};

void MeshGenerator::generateMesh(std::int16_t originX, std::int16_t originZ, const ChunkBlocks& chunk, const ChunkBlocks& cFront, const ChunkBlocks& cBack, const ChunkBlocks& cLeft, const ChunkBlocks& cRight) {
	BlockType top
	, bottom
	, left
	, right
	, front
	, back;

	auto setNeighbors = [&](std::int16_t x, std::int16_t y, std::int16_t z) {
		// x
		if (x - 1 < 0)
			left = cLeft.getBlock(CHUNK_WIDTH - 1, y, z);
		else
			left = chunk.getBlock(x - 1, y, z);

		if (x + 1 >= CHUNK_WIDTH)
			right = cRight.getBlock(0, y, z);
		else
			right = chunk.getBlock(x + 1, y, z);

		//z

		if (z - 1 < 0)
			back = cBack.getBlock(x, y, CHUNK_WIDTH - 1);
		else
			back = chunk.getBlock(x, y, z - 1);

		if (z + 1 >= CHUNK_WIDTH)
			front = cFront.getBlock(x, y, 0);
		else
			front = chunk.getBlock(x, y, z + 1);

		// y
		if (y - 1 < 0)
			bottom = BlockType::VOID;
		else
			bottom = chunk.getBlock(x, y - 1, z);

		if (y + 1 >= CHUNK_HEIGHT)
			top = BlockType::VOID;
		else
			top = chunk.getBlock(x, y + 1, z);
	};

	for (std::int16_t x = 0; x < CHUNK_WIDTH; x++) {
		for (std::int16_t y = 0; y < CHUNK_HEIGHT; y++) {
			for (std::int16_t z = 0; z < CHUNK_WIDTH; z++) {
				if (chunk.getBlock(x, y, z) == BlockType::VOID)
					continue;
				setNeighbors(x, y, z);

				std::int16_t oX = x + originX;
				std::int16_t oZ = z + originZ;
				if (top == BlockType::VOID)
					addFace(oX, y, oZ, s_top);
				if (bottom == BlockType::VOID)
					addFace(oX, y, oZ, s_bottom);
				if (left == BlockType::VOID)
					addFace(oX, y, oZ, s_left);
				if (right == BlockType::VOID)
					addFace(oX, y, oZ, s_right);
				if (front == BlockType::VOID)
					addFace(oX, y, oZ, s_front);
				if (back == BlockType::VOID)
					addFace(oX, y, oZ, s_back);
			}
		}
	}
}

const Mesh& MeshGenerator::getMesh() const {
	return m_mesh;
}

void MeshGenerator::cleanUp() {
	m_mesh.vertices.clear();
	m_mesh.textureCoords.clear();
	m_mesh.indices.clear();

	m_mesh.vertices.shrink_to_fit();
	m_mesh.textureCoords.shrink_to_fit();
	m_mesh.indices.shrink_to_fit();
}

void MeshGenerator::addFace(std::int16_t x, std::int16_t y, std::int16_t z, const std::array<GLfloat, 12>& face) {
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
		m_mesh.vertices.push_back(x + face[faceIndex++]);
		m_mesh.vertices.push_back(y + face[faceIndex++]);
		m_mesh.vertices.push_back(z + face[faceIndex++]);
	}
}
