#include "stdafx.h"
#include "ChunkManager.h"

ChunkManager::~ChunkManager() {
	m_chunks.clear();
}

void ChunkManager::loadChunk(const VecXZ& pos, const Chunk& chunk) {
	m_chunks.emplace(std::make_pair(pos, chunk));
}

void ChunkManager::unloadChunk(const VecXZ& pos) {
	m_chunks.erase(pos);
}

void ChunkManager::setBlock(std::int16_t x, std::int16_t y, std::int16_t z, BlockType id) {
	m_chunks[{x / CHUNK_WIDTH, z / CHUNK_WIDTH}].setBlock(x % CHUNK_WIDTH, y,  z % CHUNK_WIDTH, id);
}

BlockType ChunkManager::getBlock(std::int16_t x, std::int16_t y, std::int16_t z) const {
	return m_chunks.at({x / CHUNK_WIDTH, z / CHUNK_WIDTH}).getBlock(x % CHUNK_WIDTH, y, z % CHUNK_WIDTH);
}
