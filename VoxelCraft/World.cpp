#include "stdafx.h"
#include "World.h"

World::World() {
	m_mapGenerator = std::make_unique<OverworldGenerator>();
}

void World::update(const Camera& camera, MasterRenderer& renderer) {
	m_camPosition = { (int)(camera.getPosition().x / CHUNK_WIDTH), (int)(camera.getPosition().z / CHUNK_WIDTH)};
	if (m_camPosition != m_lastCamPosition) {
		readyChunk(m_camPosition.x, m_camPosition.y);
		readyChunk(m_camPosition.x+1, m_camPosition.y);
		readyChunk(m_camPosition.x-1, m_camPosition.y);
		readyChunk(m_camPosition.x, m_camPosition.y+1);
		readyChunk(m_camPosition.x, m_camPosition.y-1);

		for (std::int16_t i = 0; i < m_chunkBatch.size(); i++) {
			if (m_chunks.createMesh(m_chunkBatch[i]) && m_chunks.hasMesh(m_chunkBatch[i])) {
				renderer.addChunk(m_chunks.getChunkModels(m_chunkBatch[i]));
			}
		}
	}
	m_lastCamPosition = m_camPosition;
}

void World::readyChunk(std::int16_t x, std::int16_t z) {
	if (!m_chunks.doesChunkExist({ x, z })) {
		m_chunks.loadChunk({ x, z }, m_mapGenerator->generateChunk({ x, z }));
		m_chunkBatch.push_back({ x, z });
	}
}
