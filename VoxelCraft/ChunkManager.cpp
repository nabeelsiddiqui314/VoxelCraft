#include "stdafx.h"
#include "ChunkManager.h"

ChunkManager::~ChunkManager() {
	m_chunks.clear();
}

void ChunkManager::loadChunk(const VecXZ& pos, const ChunkBlocks& chunkblocks) {
	Chunk chunk;
	chunk.chunk = chunkblocks;
	m_chunks.emplace(std::make_pair(pos, chunk));
}

void ChunkManager::unloadChunk(const VecXZ& pos) {
	m_chunks.erase(pos);
}

bool ChunkManager::doesChunkExist(const VecXZ& pos) const {
	return m_chunks.find(pos) != m_chunks.end();
}

void ChunkManager::setBlock(const VecXZ& pos, std::int16_t x, std::int16_t y, std::int16_t z, BlockType id) {
	m_chunks[pos].chunk.setBlock(x, y, z, id);
}

BlockType ChunkManager::getBlock(const VecXZ& pos, std::int16_t x, std::int16_t y, std::int16_t z) const {
	return m_chunks.at(pos).chunk.getBlock(x, y, z);
}

bool ChunkManager::createMesh(const VecXZ& pos) {
	if (!m_chunks[pos].hasMeshGenerated && 
		doesChunkExist({ pos.x, pos.z + 1 }) &&
		doesChunkExist({ pos.x, pos.z - 1 }) &&
		doesChunkExist({ pos.x - 1, pos.z }) &&
		doesChunkExist({ pos.x + 1, pos.z })) {
		m_chunks[pos].models.generateMesh(pos.x * CHUNK_WIDTH, pos.z * CHUNK_WIDTH,
			m_chunks[pos].chunk,
			m_chunks[{ pos.x, pos.z + 1 }].chunk,
			m_chunks[{ pos.x, pos.z - 1 }].chunk,
			m_chunks[{ pos.x - 1, pos.z }].chunk,
			m_chunks[{ pos.x + 1, pos.z }].chunk);
		if (!m_chunks[pos].models.getBlockModel().has_value())
			return false;
		m_chunks[pos].hasMeshGenerated = true;
		m_chunks[pos].models.cleanUp();
		return true;
	}
	return false;
}

const Model& ChunkManager::getChunkModels(const VecXZ& pos) const {
	return m_chunks.at(pos).models.getBlockModel().value();
}

bool ChunkManager::hasMesh(const VecXZ& pos) const {
	return m_chunks.at(pos).hasMeshGenerated;
}
