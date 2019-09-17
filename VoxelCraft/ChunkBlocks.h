#pragma once
#include <array>
#include "BlockTypes.h"

const std::int32_t CHUNK_WIDTH = 16;
const std::int32_t CHUNK_HEIGHT = 50;
const std::int32_t CHUNK_VOLUME = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;

class ChunkBlocks {
public:
	ChunkBlocks();
public:
	void setBlock(std::int16_t x, std::int16_t y, std::int16_t z, BlockType id);
	BlockType getBlock(std::int16_t x, std::int16_t y, std::int16_t z) const;
private:
	std::array<BlockType, CHUNK_VOLUME> m_blocks;
};