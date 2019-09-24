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

void ChunkManager::setMesh(Mesh& mesh, const VecXZ& pos, std::int16_t y) {
	m_chunks[pos].setMesh(mesh, y);
}

const Chunks& ChunkManager::getChunkAt(const VecXZ& pos) const {
	return m_chunks.at(pos);
}

void ChunkManager::render(const VecXZ & pos, MasterRenderer & renderer) {
	m_chunks[pos].render(renderer);
}
