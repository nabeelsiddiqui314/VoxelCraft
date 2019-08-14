#include "stdafx.h"
#include "World.h"

World::World() {
	m_mapGenerator = std::make_unique<FlatGenerator>();
	m_chunks.loadChunk({ 0 , 0 }, m_mapGenerator->generateChunk({0,0}));
	m_chunks.loadChunk({ -1, 0 }, ChunkBlocks());
	m_chunks.loadChunk({ 1 , 0 }, ChunkBlocks());
	m_chunks.loadChunk({ 0 , 1 }, ChunkBlocks());
	m_chunks.loadChunk({ 0 ,-1 }, ChunkBlocks());
	m_chunks.createMesh({ 0,0 });
	m_chunkModels.emplace_back(m_chunks.getChunkModels({0,0}));
}

void World::update(MasterRenderer& renderer) {
	renderer.addChunk(&m_chunks.getChunkModels({ 0,0 }));
}
