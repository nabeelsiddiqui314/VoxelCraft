#include "stdafx.h"
#include "ChunkBlocks.h"

ChunkBlocks::ChunkBlocks() {
	m_blocks.fill(BlockType::VOID);
}

void ChunkBlocks::setBlock(std::int16_t x, std::int16_t y, std::int16_t z, BlockType id) {
	m_blocks[x + CHUNK_WIDTH * (y + CHUNK_HEIGHT * z)] = id;
}

BlockType ChunkBlocks::getBlock(std::int16_t x, std::int16_t y, std::int16_t z) const {
	return m_blocks[x + CHUNK_WIDTH * (y + CHUNK_HEIGHT * z)];
}
