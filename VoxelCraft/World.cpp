#include "stdafx.h"
#include "World.h"

World::World() 
	: m_meshGenerator(&m_chunks) {
	m_mapGenerator = std::make_unique<FlatGenerator>();
	m_chunks.loadChunk({ 0 , 0 }, m_mapGenerator->generateChunk({ 0,0 }));
	m_chunks.loadChunk({ -1, 0 }, Chunk());
	m_chunks.loadChunk({ 1 , 0 }, Chunk());
	m_chunks.loadChunk({ 0 , 1 }, Chunk());
	m_chunks.loadChunk({ 0 ,-1 }, Chunk());
	m_chunkModels.emplace_back(m_meshGenerator.generateMesh({0,0}));
}

Model& World::get() {
	return m_chunkModels[0];
}

void World::update() {
	
}
