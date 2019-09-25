#include "stdafx.h"
#include "World.h"

World::World() : m_renderDistance(5) {
	m_mapGenerator = std::make_unique<FlatGenerator>(256);
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
		for (std::int16_t x = m_camPosition.x - m_renderDistance; x <= m_camPosition.x + m_renderDistance; x++) {
			for (std::int16_t z = m_camPosition.z - m_renderDistance; z <= m_camPosition.z + m_renderDistance; z++) {
				if (x > m_camPosition.x + m_renderDistance || z > m_camPosition.z + m_renderDistance
					|| x < m_camPosition.x - m_renderDistance || z < m_camPosition.z - m_renderDistance) {
					if (m_chunks.doesChunkExist({ x,z })) {
						std::lock_guard<std::mutex> lock(m_mutex);
						m_chunks.unloadChunk({ x,z });
					}
				}
			}
		}

		for (std::int16_t x = m_camPosition.x - m_renderDistance; x <= m_camPosition.x + m_renderDistance; x++) {
			for (std::int16_t z = m_camPosition.z - m_renderDistance; z <= m_camPosition.z + m_renderDistance; z++) {
				if (!m_chunks.doesChunkExist({ x,z })) {
					Chunks chunk;
					chunk = m_mapGenerator->generateChunk({ x,z });

					std::unique_lock<std::mutex> lock(m_mutex);
					m_chunks.loadChunk({ x,z }, chunk);
					lock.unlock();
					break;
				}
			}
		}

		for (std::int16_t x = m_camPosition.x - m_renderDistance; x <= m_camPosition.x + m_renderDistance; x++) {
			for (std::int16_t z = m_camPosition.z - m_renderDistance; z <= m_camPosition.z + m_renderDistance; z++) {
				if (!m_chunks.doesChunkExist({ x,z }) || !m_chunks.doesChunkExist({ x + 1,z }) ||
					!m_chunks.doesChunkExist({ x - 1, z }) || !m_chunks.doesChunkExist({ x,z + 1}) ||
					!m_chunks.doesChunkExist({ x,z - 1}))
					continue;

				for (std::size_t y = 0; y < Chunks::HEIGHT; y++) {
					if (!m_chunks.getChunkAt({ x,z }).hasMesh(y)) {
						const Segment& chunk = m_chunks.getChunkAt({ x,z }).getSegment(y);
						const Segment& front = m_chunks.getChunkAt({ x,z + 1}).getSegment(y);
						const Segment& back = m_chunks.getChunkAt({ x,z - 1}).getSegment(y);
						const Segment& left = m_chunks.getChunkAt({ x - 1 ,z }).getSegment(y);
						const Segment& right = m_chunks.getChunkAt({ x + 1,z }).getSegment(y);
						Segment top;
						Segment bottom;
						if (y > 0)
							bottom = m_chunks.getChunkAt({ x,z }).getSegment(y - 1);
						if (y < Chunks::HEIGHT - 1)
							top = m_chunks.getChunkAt({ x,z }).getSegment(y + 1);
						
						Mesh mesh;
						if (y > 0 && y < Chunks::HEIGHT - 1) {
							ChunkModelsMaker(mesh, x * Segment::WIDTH, y * Segment::WIDTH, z * Segment::WIDTH,
								&chunk, &top, &bottom, &left, &right, &front, &back);
						}
						else if (y > 0) {
							ChunkModelsMaker(mesh, x * Segment::WIDTH, y * Segment::WIDTH, z * Segment::WIDTH,
								&chunk, nullptr, &bottom, &left, &right, &front, &back);
						}
						else {
							ChunkModelsMaker(mesh, x * Segment::WIDTH, y * Segment::WIDTH, z * Segment::WIDTH,
								&chunk, &top, nullptr, &left, &right, &front, &back);
						}

						std::unique_lock<std::mutex> lock(m_mutex);
						m_chunks.setMesh(mesh, {x, z}, y);
						lock.unlock();
						break;
					}
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}