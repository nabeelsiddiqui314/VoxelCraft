#include "stdafx.h"
#include "ChunkManager.h"

ChunkManager::~ChunkManager() {
	m_chunks.clear();
}

void ChunkManager::loadChunk(const VecXZ& pos, const Chunks& chunks) {
	m_chunks.emplace(std::make_pair(pos, chunks));
	m_chunks[pos].makeBoxes(pos.x, pos.z);
}

void ChunkManager::unloadChunks(const std::function<bool(const VecXZ& pos)>& cond) {
	for (auto itr = m_chunks.begin(); itr != m_chunks.end();) {
		if (cond(itr->first)) {
			m_chunks[itr->first].cleanUp();
			itr = m_chunks.erase(itr);
		}
		else
			itr++;
	}
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

void ChunkManager::makeMesh(const VecXZ& pos) {
	if (doesChunkExist({ pos.x - 1, pos.z }) && 
		doesChunkExist({ pos.x + 1, pos.z }) && 
		doesChunkExist({ pos.x,     pos.z + 1}) &&
		doesChunkExist({ pos.x,     pos.z - 1})) {
		m_chunks[pos].makeMesh(pos.x, pos.z, &m_chunks[{pos.x - 1, pos.z}], &m_chunks[{pos.x + 1, pos.z}],
			&m_chunks[{pos.x, pos.z + 1}], &m_chunks[{pos.x, pos.z - 1}]);
	}
}

const Chunks& ChunkManager::getChunkAt(const VecXZ& pos) const {
	return m_chunks.at(pos);
}

void ChunkManager::regenMesh(const VecXZ& pos, std::int16_t y) {
	m_chunks[pos].regenMesh(y);
}

void ChunkManager::render(const VecXZ& pos, MasterRenderer& renderer, const Frustum& frustum) {
	m_chunks[pos].render(renderer, frustum);
}
