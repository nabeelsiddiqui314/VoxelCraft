#include "stdafx.h"
#include "World.h"

World::World() : m_renderDistance(16) {
	m_mapGenerator = std::make_unique<OverworldGenerator>();
	m_threads.emplace_back([&]() {
		makeSector();
	});
	m_threads.emplace_back([&]() {
		updateBlocks();
	});
}

World::~World() {
	m_running = false;
	for (auto& thread : m_threads) {
		thread.join();
	}
}

void World::setBlock(std::int64_t x, std::int64_t y, std::int64_t z, BlockType block) {
	int X = x, Y = y, Z = z;
	const auto& pos = getSectorPos(x, z);

	std::lock_guard<std::recursive_mutex> lock(m_mutex);
	if (m_sectors.doesSectorExist(pos)) {
		updateMeshes(pos, y / Segment::WIDTH);
		updateMeshes(pos, (y + 1) / Segment::WIDTH);
		updateMeshes(pos, (y - 1) / Segment::WIDTH);
		std::tie(x, y, z) = getBlockPos(x, y, z);
		m_sectors.setBlock(pos, x, y, z, block);

		addToUpdates(X, Y, Z);
	}
}

BlockType World::getBlock(std::int64_t x, std::int64_t y, std::int64_t z) const {
	const auto& pos = getSectorPos(x, z);
	
	std::lock_guard<std::recursive_mutex> lock(m_mutex);
	if (m_sectors.doesSectorExist(pos)) {
		std::tie(x, y, z) = getBlockPos(x, y, z);
		return m_sectors.getBlock(pos, x, y, z);
	}
	return BlockType::VOID;
}

void World::update(const Camera& camera) {
	std::lock_guard<std::recursive_mutex> lock(m_mutex);
	m_sectors.unloadSector([&](const VecXZ& pos) {
		return pos.x < m_camPosition.x - m_renderDistance || pos.z < m_camPosition.z - m_renderDistance
			|| pos.x > m_camPosition.x + m_renderDistance || pos.z > m_camPosition.z + m_renderDistance;
	});

	m_camPosition = { (int)camera.getPosition().x / Segment::WIDTH, (int)camera.getPosition().z / Segment::WIDTH };
}

void World::renderSector(MasterRenderer& renderer, const Frustum& frustum) {
	for (std::int16_t x = m_camPosition.x - m_renderDistance; x <= m_camPosition.x + m_renderDistance; x++) {
		for (std::int16_t z = m_camPosition.z - m_renderDistance; z <= m_camPosition.z + m_renderDistance; z++) {
			std::lock_guard<std::recursive_mutex> lock(m_mutex);
			if (!m_sectors.doesSectorExist({x,z}))
				continue;
			m_sectors.render({x,z}, renderer, frustum);
		}
	}
}

void World::makeSector() {
	while (m_running) {
		for (std::int16_t x = m_camPosition.x - m_currentRadius; x <= m_camPosition.x + m_currentRadius; x++) {
			for (std::int16_t z = m_camPosition.z - m_currentRadius; z <= m_camPosition.z + m_currentRadius; z++) {
				makeEditedMeshes();

				if (!m_sectors.doesSectorExist({ x, z })) {
					const auto sector = m_mapGenerator->generateSector({ x,z });
					std::lock_guard<std::recursive_mutex> lock(m_mutex);
					m_sectors.loadSector({ x,z }, sector);
				}
				else {
					m_sectors.makeMesh({ x,z });
				}
			}
		}
		m_currentRadius++;
		m_currentRadius %= m_renderDistance;
		std::this_thread::sleep_for(std::chrono::microseconds(10));
	}
}

void World::updateBlocks() {
	while (m_running) {
		std::unique_lock<std::recursive_mutex> lock(m_mutex);
		for (auto itr = m_updateList.begin(); itr != m_updateList.end();) {
			int x = itr->x;
			int y = itr->y;
			int z = itr->z;

			if (BlockCodex::getBlockData(getBlock(x, y, z)).updateHandler->update(*this, x, y, z)) {
				itr = m_updateList.erase(itr);
				break;
			}
			else {
				itr++;
			}
		}
		lock.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void World::makeEditedMeshes() {
	std::unique_lock<std::recursive_mutex> lock(m_mutex);
	for (auto itr = m_regenSectors.begin(); itr != m_regenSectors.end();) {
		if (m_sectors.doesSectorExist(*itr)) {
			const auto pos = *itr;
			lock.unlock();
			m_sectors.makeMesh(pos);
			lock.lock();
			itr = m_regenSectors.erase(itr);
		}
		else
			itr++;
	}
}

void World::updateMeshes(const VecXZ& pos, std::int16_t y) {
	if (y > 0) {
		m_sectors.regenMesh(pos, y - 1);
	}
	if (y < Sector::HEIGHT - 1) {
		m_sectors.regenMesh(pos, y + 1);
	}

	m_sectors.regenMesh(pos, y);
	m_sectors.regenMesh({ pos.x + 1, pos.z     }, y);
	m_sectors.regenMesh({ pos.x    , pos.z + 1 }, y);
	m_sectors.regenMesh({ pos.x - 1, pos.z     }, y);
	m_sectors.regenMesh({ pos.x    , pos.z - 1 }, y);

	m_regenSectors.emplace(pos);
	m_regenSectors.insert({pos.x + 1, pos.z     });
	m_regenSectors.insert({pos.x    , pos.z + 1 });
	m_regenSectors.insert({pos.x - 1, pos.z     });
	m_regenSectors.insert({pos.x    , pos.z - 1 });
}

void World::addToUpdates(int x, int y, int z) {
	auto tryAdd = [&](int X, int Y, int Z) {
		if (BlockCodex::getBlockData(getBlock(X, Y, Z)).updateHandler->isUpdatable()) {
			m_updateList.insert({ X, Y, Z });
		}
	};

	tryAdd(x    , y,     z    );
	tryAdd(x + 1, y,     z    );
	tryAdd(x - 1, y,     z    );
	tryAdd(x,     y + 1, z    );
	tryAdd(x,     y - 1, z    );
	tryAdd(x,     y,     z + 1);
	tryAdd(x,     y,     z - 1);
}

const VecXZ World::getSectorPos(std::int64_t x, std::int64_t z) const {
	return {x / Segment::WIDTH, z / Segment::WIDTH};
}

const std::tuple<int, int, int> World::getBlockPos(std::int64_t x, std::int64_t y, std::int64_t z) const {
	return std::tuple<int, int, int>(abs(x) % Segment::WIDTH, y, abs(z) % Segment::WIDTH);
}
