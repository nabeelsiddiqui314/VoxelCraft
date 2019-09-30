#include "stdafx.h"
#include "World.h"

World::World() : m_renderDistance(5) {
	m_mapGenerator = std::make_unique<OverworldGenerator>();
	m_threads.emplace_back([&]() {
		loadChunks();
	});
}

World::~World() {
	m_running = false;
	for (auto& thread : m_threads) {
		thread.join();
	}
}

void World::update(const Camera& camera) {
	m_camPosition = { (std::int16_t)(camera.getPosition().x / Segment::WIDTH), (std::int16_t)(camera.getPosition().z / Segment::WIDTH)};
	if (m_chunks.doesChunkExist(m_camPosition)) {
		std::int16_t x, z;
		if (camera.getPosition().x >= 0)
			x = (int)(camera.getPosition().x) % Segment::WIDTH;
		else
			x = Segment::WIDTH - abs((int)camera.getPosition().x) % Segment::WIDTH;

		if (camera.getPosition().z >= 0)
			z = (int)(camera.getPosition().z) % Segment::WIDTH;
		else
			z = Segment::WIDTH - abs((int)camera.getPosition().z) % Segment::WIDTH;

		if (m_chunks.getBlock(m_camPosition, x, (int)floor(camera.getPosition().y), z) == BlockType::VOID) {
			m_chunks.setBlock(m_camPosition, x, (int)floor(camera.getPosition().y), z, BlockType::SAND);
			m_chunks.regenMesh(m_camPosition, camera.getPosition().y / Segment::WIDTH );
		}
	}
}

void World::renderChunks(MasterRenderer& renderer) {
	std::lock_guard<std::mutex> lock(m_mutex);
	for (std::int16_t x = m_camPosition.x - m_renderDistance; x <= m_camPosition.x + m_renderDistance; x++) {
		for (std::int16_t z = m_camPosition.z - m_renderDistance; z <= m_camPosition.z + m_renderDistance; z++) {
			if (!m_chunks.doesChunkExist({x,z}))
				continue;

			m_chunks.render({x,z}, renderer);
		}
	}
}

void World::loadChunks() {
	while (m_running) {
		m_chunks.unloadChunks([&](const VecXZ& pos) {
			return pos.x < m_camPosition.x - m_renderDistance || pos.z < m_camPosition.z - m_renderDistance
				|| pos.x > m_camPosition.x + m_renderDistance || pos.z > m_camPosition.z + m_renderDistance;
		});

		for (std::int16_t x = m_camPosition.x - m_chunkLoadRadius; x <= m_camPosition.x + m_chunkLoadRadius; x++) {
			for (std::int16_t z = m_camPosition.z - m_chunkLoadRadius; z <= m_camPosition.z + m_chunkLoadRadius; z++) {
				if (!m_chunks.doesChunkExist({ x,z })) {
					Chunks chunk;
					chunk = m_mapGenerator->generateChunk({ x,z });

					std::unique_lock<std::mutex> lock(m_mutex);
					m_chunks.loadChunk({ x,z }, chunk);
					lock.unlock();
				}
				else {
					m_chunks.makeMesh({ x,z });
				}
			}
		}

		m_chunkLoadRadius++;
		m_chunkLoadRadius %= m_renderDistance;

		std::this_thread::sleep_for(std::chrono::microseconds(10));
	}
}