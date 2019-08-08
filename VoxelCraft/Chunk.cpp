#include "stdafx.h"
#include "Chunk.h"

Chunk::Chunk() {
	m_blocks.fill(BlockType::VOID);
}

void Chunk::setBlock(std::int16_t x, std::int16_t y, std::int16_t z, BlockType id) {
	m_blocks[x + CHUNK_WIDTH * (y + CHUNK_WIDTH * z)] = id;
}

BlockType Chunk::getBlock(std::int16_t x, std::int16_t y, std::int16_t z) const {
	return m_blocks[x + CHUNK_WIDTH * (y + CHUNK_WIDTH * z)];
}
