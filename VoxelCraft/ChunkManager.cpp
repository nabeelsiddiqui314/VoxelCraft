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

void ChunkManager::createMesh(const VecXZ& pos) {
	if ( doesChunkExist({ pos.x, pos.z + 1 }) &&
		 doesChunkExist({ pos.x, pos.z - 1 }) &&
		 doesChunkExist({ pos.x - 1, pos.z }) &&
		 doesChunkExist({ pos.x + 1, pos.z })) {
		m_chunks[pos].models.generateMeshes(pos.x * CHUNK_WIDTH, pos.z * CHUNK_WIDTH,
			m_chunks[pos].chunk,
			m_chunks[{ pos.x, pos.z + 1 }].chunk,
			m_chunks[{ pos.x, pos.z - 1 }].chunk,
			m_chunks[{ pos.x - 1, pos.z }].chunk,
			m_chunks[{ pos.x + 1, pos.z }].chunk);
		m_chunks[pos].hasMeshGenerated = true;
	}
}

void ChunkManager::addMeshesToModel(const VecXZ& pos) {
	m_chunks[pos].models.addMeshesToModels();
}

const ChunkModels& ChunkManager::getChunkModels(const VecXZ& pos) const {
	return m_chunks.at(pos).models.getModels();
}

bool ChunkManager::hasMadeMesh(const VecXZ& pos) const {
	return m_chunks.at(pos).hasMeshGenerated;
}

bool ChunkManager::hasMesh(const VecXZ& pos) {
	return m_chunks.at(pos).models.getModels().solid.model.has_value();
}