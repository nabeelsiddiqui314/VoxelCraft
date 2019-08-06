#pragma once
#include <array>
#include "BlockTypes.h"
#include <glm/glm.hpp>

const int CHUNK_AREA = 16;
const int CHUNK_HEIGHT = 16;
const int CHUNK_VOLUME = CHUNK_AREA * CHUNK_AREA * CHUNK_HEIGHT;

class Chunk {
public:
	Chunk();
public:
	void setBlock(int x, int y, int z, Block_id id);
	Block_id getBlock(int x, int y, int z) const;
private:
	std::array<Block_id, CHUNK_VOLUME> m_blocks;
};