#pragma once
#include <array>
#include "BlockTypes.h"

const int CHUNK_WIDTH = 16;
const int CHUNK_HEIGHT = 16;
const int CHUNK_VOLUME = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;

class Chunk {
public:
	Chunk();
public:
	void setBlock(std::int16_t x, std::int16_t y, std::int16_t z, Block_id id);
	Block_id getBlock(std::int16_t x, std::int16_t y, std::int16_t z) const;
private:
	std::array<Block_id, CHUNK_VOLUME> m_blocks;
};