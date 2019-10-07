#include "stdafx.h"
#include "World.h"

World::World() : m_renderDistance(16) {
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
	std::lock_guard<std::mutex> lock(m_mutex);
	m_chunks.unloadChunks([&](const VecXZ& pos) {
		return pos.x < m_camPosition.x - m_renderDistance || pos.z < m_camPosition.z - m_renderDistance
			|| pos.x > m_camPosition.x + m_renderDistance || pos.z > m_camPosition.z + m_renderDistance;
	});

	m_camPosition = { (int)camera.getPosition().x / Segment::WIDTH, (int)camera.getPosition().z / Segment::WIDTH };
}

void World::renderChunks(MasterRenderer& renderer, const Frustum& frustum) {
	for (std::int16_t x = m_camPosition.x - m_renderDistance; x <= m_camPosition.x + m_renderDistance; x++) {
		for (std::int16_t z = m_camPosition.z - m_renderDistance; z <= m_camPosition.z + m_renderDistance; z++) {
			std::lock_guard<std::mutex> lock(m_mutex);
			if (!m_chunks.doesChunkExist({x,z}))
				continue;
			m_chunks.render({x,z}, renderer, frustum);
		}
	}
}

void World::loadChunks() {
	while (m_running) {
		for (std::int16_t x = m_camPosition.x - m_renderDistance; x <= m_camPosition.x + m_renderDistance; x++) {
			for (std::int16_t z = m_camPosition.z - m_renderDistance; z <= m_camPosition.z + m_renderDistance; z++) {
				makeEditedMeshes();

				if (!m_chunks.doesChunkExist({ x, z })) {
					const auto chunk = m_mapGenerator->generateChunk({ x,z });
					std::unique_lock<std::mutex> lock(m_mutex);
					m_chunks.loadChunk({ x,z }, chunk);
					lock.unlock();
					break;
				}
				else {
					m_chunks.makeMesh({ x,z });
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::microseconds(10));
	}
}

void World::makeEditedMeshes() {
	std::unique_lock<std::mutex> lock(m_mutex);
	for (auto itr = m_regenChunks.begin(); itr != m_regenChunks.end();) {
		if (m_chunks.doesChunkExist(*itr)) {
			const auto pos = *itr;
			lock.unlock();
			m_chunks.makeMesh(pos);
			lock.lock();
			itr = m_regenChunks.erase(itr);
		}
		else
			itr++;
	}
}