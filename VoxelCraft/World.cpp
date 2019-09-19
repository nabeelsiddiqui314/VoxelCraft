#include "stdafx.h"
#include "World.h"

World::World() : m_renderDistance(4) {
	m_mapGenerator = std::make_unique<FlatGenerator>(256);
}

void World::update(const Camera& camera) {
	m_camPosition = { (std::int16_t)(camera.getPosition().x / Segment::WIDTH), (std::int16_t)(camera.getPosition().z / Segment::WIDTH)};
	if (m_camPosition != m_lastCamPosition) {
		for (std::int16_t i = 0; i < m_chunkBatch.size(); i++) {
			if (m_chunkBatch[i].x > m_camPosition.x + m_renderDistance || m_chunkBatch[i].z > m_camPosition.z + m_renderDistance
				|| m_chunkBatch[i].x < m_camPosition.x - m_renderDistance || m_chunkBatch[i].z < m_camPosition.z - m_renderDistance) {
				m_chunks.unloadChunk(m_chunkBatch[i]);
			}
		}
		m_chunkBatch.clear();
		for (std::int16_t x = m_camPosition.x - m_renderDistance; x <= m_camPosition.x + m_renderDistance; x++) {
			for (std::int16_t z = m_camPosition.z - m_renderDistance; z <= m_camPosition.z + m_renderDistance; z++) {
				m_chunkBatch.push_back({x,z});
			}
		}
	}
	m_lastCamPosition = m_camPosition;

	//if (m_loadTick.getElapsedTime().asMilliseconds() > 10) {
		for (std::int16_t i = 0; i < m_chunkBatch.size(); i++) {
			if (!m_chunks.doesChunkExist(m_chunkBatch[i])) {
				m_chunks.loadChunk(m_chunkBatch[i], m_mapGenerator->generateChunk(m_chunkBatch[i]));
				break;
			}
		}

		for (std::int16_t i = 0; i < m_chunkBatch.size(); i++) {
			if (!m_chunks.doesChunkExist(m_chunkBatch[i]))
				continue;

			if (m_chunks.createMesh(m_chunkBatch[i]))
				break;
		}
		//m_loadTick.restart();
	//}
}

void World::renderChunks(MasterRenderer& renderer) {
	for (std::int16_t i = 0; i < m_chunkBatch.size(); i++) {
		if (!m_chunks.doesChunkExist(m_chunkBatch[i]))
			continue;

		m_chunks.render(m_chunkBatch[i], renderer);
	}
}