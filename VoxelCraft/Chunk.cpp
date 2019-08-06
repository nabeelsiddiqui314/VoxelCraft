#include "stdafx.h"
#include "Chunk.h"

Chunk::Chunk() {
	m_blocks.fill(0);
}

void Chunk::setBlock(int x, int y, int z, Block_id id) {
	m_blocks[x + CHUNK_AREA * (y + CHUNK_AREA * z)] = id;
}

Block_id Chunk::getBlock(int x, int y, int z) const {
	return m_blocks[x + CHUNK_AREA * (y + CHUNK_AREA * z)];
}
