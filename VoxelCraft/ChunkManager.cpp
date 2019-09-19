#include "stdafx.h"
#include "ChunkManager.h"

ChunkManager::~ChunkManager() {
	m_chunks.clear();
}

void ChunkManager::loadChunk(const VecXZ& pos, const Chunks& chunks) {
	m_chunks.emplace(std::make_pair(pos, chunks));
}

void ChunkManager::unloadChunk(const VecXZ& pos) {
	m_chunks.erase(pos);
}

bool ChunkManager::doesChunkExist(const VecXZ& pos) const {
	return m_chunks.find(pos) != m_chunks.end();
}

void ChunkManager::setBlock(const VecXZ& pos, std::int16_t x, std::int16_t y, std::int16_t z, BlockType id) {
	m_chunks[pos].setBlock(x, y, z, id);
}

BlockType ChunkManager::getBlock(const VecXZ& pos, std::int16_t x, std::int16_t y, std::int16_t z) const {
	return m_chunks.at(pos).getBlock(x, y, z);
}

bool ChunkManager::createMesh(const VecXZ& pos) {
	if ( doesChunkExist({ pos.x, pos.z + 1 }) &&
		 doesChunkExist({ pos.x, pos.z - 1 }) &&
		 doesChunkExist({ pos.x - 1, pos.z }) &&
		 doesChunkExist({ pos.x + 1, pos.z })) {
		return m_chunks[pos].createMesh(pos.x * Segment::WIDTH, pos.z * Segment::WIDTH,
			&m_chunks[{ pos.x - 1, pos.z }],
			&m_chunks[{ pos.x + 1, pos.z }],
			&m_chunks[{ pos.x, pos.z + 1 }],
			&m_chunks[{ pos.x, pos.z - 1}]);
	}
	return false;
}

void ChunkManager::render(const VecXZ & pos, MasterRenderer & renderer) {
	m_chunks[pos].render(renderer);
}
