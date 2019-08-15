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
	m_chunks[pos].models.createMesh(pos.x * CHUNK_WIDTH, pos.z * CHUNK_WIDTH,
		m_chunks[pos].chunk,
		doesChunkExist({ pos.x, pos.z + 1 }) ? m_chunks[{ pos.x, pos.z + 1 }].chunk : ChunkBlocks(),
		doesChunkExist({ pos.x, pos.z - 1 }) ? m_chunks[{ pos.x, pos.z - 1 }].chunk : ChunkBlocks(),
		doesChunkExist({ pos.x - 1, pos.z }) ? m_chunks[{ pos.x - 1, pos.z }].chunk : ChunkBlocks(),
		doesChunkExist({ pos.x + 1, pos.z }) ? m_chunks[{ pos.x + 1, pos.z }].chunk : ChunkBlocks());
	m_chunks[pos].hasMeshGenerated = true;
	m_chunks[pos].models.cleanUp();
}

const Model& ChunkManager::getChunkModels(const VecXZ& pos) const {
	return m_chunks.at(pos).models.getModel();
}

bool ChunkManager::hasMesh(const VecXZ& pos) const {
	return m_chunks.at(pos).hasMeshGenerated;
}
