#include "stdafx.h"
#include "World.h"

World::World() : m_renderDistance(2) {
	m_mapGenerator = std::make_unique<OverworldGenerator>();
}

void World::update(const Camera& camera) {
	m_camPosition = { (std::int16_t)(camera.getPosition().x / Segment::WIDTH), (std::int16_t)(camera.getPosition().z / Segment::WIDTH)};
	if (m_camPosition != m_lastCamPosition) {
		//for (std::int16_t i = 0; i < m_chunkBatch.size(); i++) {
		//	if (m_chunkBatch[i].x > m_camPosition.x + m_renderDistance || m_chunkBatch[i].z > m_camPosition.z + m_renderDistance
		//		|| m_chunkBatch[i].x < m_camPosition.x - m_renderDistance || m_chunkBatch[i].z < m_camPosition.z - m_renderDistance) {
		//		m_chunks.unloadChunk(m_chunkBatch[i]);
		//	}
		//}
		//m_chunkBatch.clear();
		//m_batchIndex = 0;
		//for (std::int16_t x = m_camPosition.x - m_renderDistance; x <= m_camPosition.x + m_renderDistance; x++) {
		//	for (std::int16_t z = m_camPosition.z - m_renderDistance; z <= m_camPosition.z + m_renderDistance; z++) {
		//		m_chunkBatch.push_back({x,z});
		//	}
		//}
	}
	m_lastCamPosition = m_camPosition;

	for (std::int16_t x = m_camPosition.x - m_renderDistance; x <= m_camPosition.x + m_renderDistance; x++) {
		for (std::int16_t z = m_camPosition.z - m_renderDistance; z <= m_camPosition.z + m_renderDistance; z++) {
			if (x > m_camPosition.x + m_renderDistance || z > m_camPosition.z + m_renderDistance
				|| x < m_camPosition.x - m_renderDistance || z < m_camPosition.z - m_renderDistance) {
				m_chunks.unloadChunk({x,z});
			}
		}
	}

	for (std::int16_t x = m_camPosition.x - m_renderDistance; x <= m_camPosition.x + m_renderDistance; x++) {
		for (std::int16_t z = m_camPosition.z - m_renderDistance; z <= m_camPosition.z + m_renderDistance; z++) {
			if (!m_chunks.doesChunkExist({x,z})) {
				m_chunks.loadChunk({ x,z }, m_mapGenerator->generateChunk({x,z}));
				break;
			}
		}		
	}

	for (std::int16_t x = m_camPosition.x - m_renderDistance; x <= m_camPosition.x + m_renderDistance; x++) {
		for (std::int16_t z = m_camPosition.z - m_renderDistance; z <= m_camPosition.z + m_renderDistance; z++) {
			if (!m_chunks.doesChunkExist({x,z}))
				continue;
	
			if (m_chunks.createMesh({x,z}))
				break;
		}
	}
	

	//if (m_loadTick.getElapsedTime().asMilliseconds() > 10) {
		//for (std::int16_t i = 0; i < m_chunkBatch.size(); i++) {
		//	if (!m_chunks.doesChunkExist(m_chunkBatch[i])) {
		//		m_chunks.loadChunk(m_chunkBatch[i], m_mapGenerator->generateChunk(m_chunkBatch[i]));
		//		break;
		//	}
		//}

		//for (std::int16_t i = 0; i < m_chunkBatch.size(); i++) {
		//	if (!m_chunks.doesChunkExist(m_chunkBatch[i]))
		//		continue;
		//
		//	if (m_chunks.createMesh(m_chunkBatch[i]))
		//		break;
		//}
		//m_loadTick.restart();
	//}
}

void World::renderChunks(MasterRenderer& renderer) {

	for (std::int16_t x = m_camPosition.x - m_renderDistance; x <= m_camPosition.x + m_renderDistance; x++) {
		for (std::int16_t z = m_camPosition.z - m_renderDistance; z <= m_camPosition.z + m_renderDistance; z++) {
			if (!m_chunks.doesChunkExist({x,z}))
				continue;

			m_chunks.render({x,z}, renderer);
		}
	}
}