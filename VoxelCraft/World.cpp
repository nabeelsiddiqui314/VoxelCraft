#include "stdafx.h"
#include "World.h"

World::World() {
	m_mapGenerator = std::make_unique<FlatGenerator>();
	for (std::int16_t x = 0; x < 5; x++) {
		for (std::int16_t z = 0; z < 5; z++) {
			m_chunkBatch.push_back({x,z});
		}
	}
}

void World::update(MasterRenderer& renderer) {
	if (m_batchIndex < m_chunkBatch.size()) {
		m_chunks.loadChunk(m_chunkBatch[m_batchIndex], m_mapGenerator->generateChunk(m_chunkBatch[m_batchIndex]));
		m_batchIndex++;
	}
	else {
		for (std::int16_t i = 0; i < m_chunkBatch.size(); i++) {
			if(m_chunks.createMesh(m_chunkBatch[i]))
				m_models.emplace_back(m_chunks.getChunkModels(m_chunkBatch[i]));
			}
	}
	for (std::int16_t i = 0; i < m_models.size(); i++) {
		renderer.addChunk(&m_models[i]);
	}
}
