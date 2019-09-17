#include "stdafx.h"
#include "World.h"

World::World() : m_renderDistance(5) {
	m_mapGenerator = std::make_unique<OverworldGenerator>();
}

void World::update(const Camera& camera) {
	m_camPosition = { (int)(camera.getPosition().x / CHUNK_WIDTH), (int)(camera.getPosition().z / CHUNK_WIDTH)};
	if (m_camPosition != m_lastCamPosition) {
		for (std::int16_t i = 0; i < m_chunkBatch.size(); i++) {
			if (m_chunkBatch[i].x > m_camPosition.x + m_renderDistance || m_chunkBatch[i].z > m_camPosition.y + m_renderDistance
				|| m_chunkBatch[i].x < m_camPosition.x - m_renderDistance || m_chunkBatch[i].z < m_camPosition.y - m_renderDistance) {
				m_chunks.unloadChunk(m_chunkBatch[i]);
			}
		}
		m_chunkBatch.clear();
		for (std::int16_t x = m_camPosition.x - m_renderDistance; x <= m_camPosition.x + m_renderDistance; x++) {
			for (std::int16_t z = m_camPosition.y - m_renderDistance; z <= m_camPosition.y + m_renderDistance; z++) {
				m_chunkBatch.push_back({x,z});
			}
		}
	}
	m_lastCamPosition = m_camPosition;

	if (m_loadTick.getElapsedTime().asMilliseconds() > 50) {
		for (std::int16_t i = 0; i < m_chunkBatch.size(); i++) {
			if (!m_chunks.doesChunkExist(m_chunkBatch[i])) {
				m_chunks.loadChunk(m_chunkBatch[i], m_mapGenerator->generateChunk(m_chunkBatch[i]));
				break;
			}
		}

		for (std::int16_t i = 0; i < m_chunkBatch.size(); i++) {
			if (!m_chunks.doesChunkExist(m_chunkBatch[i]))
				continue;

			if (!m_chunks.hasMadeMesh(m_chunkBatch[i])) {
				m_chunks.createMesh(m_chunkBatch[i]);
				if (m_chunks.hasMadeMesh(m_chunkBatch[i]))
					break;
			}
		}
		m_loadTick.restart();
	}
}

void World::renderChunks(MasterRenderer& renderer) {
	for (std::int16_t i = 0; i < m_chunkBatch.size(); i++) {
		if (!m_chunks.doesChunkExist(m_chunkBatch[i]))
			continue;

		if (m_chunks.hasMesh(m_chunkBatch[i])) {
			renderer.addChunk(m_chunks.getChunkModels(m_chunkBatch[i]));
		}
	}
}