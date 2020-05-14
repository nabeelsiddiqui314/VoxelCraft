#include "World.h"
#include "Generation/Map/OverworldGenerator.h"
#include "../OGL/Util/Camera.h"
#include "Segment/Segment.h"

World::World() : m_renderDistance(16) {
	m_mapGenerator = std::make_unique<OverworldGenerator>();
	m_camPosition.x = 0;
	m_camPosition.z = 0;
	m_threads.emplace_back([&]() {
		makeSector();
	});
}

World::~World() {
	m_running = false;
	for (auto& thread : m_threads) {
		thread.join();
	}
}

void World::setVoxel(int x, int y, int z, Voxel::Type voxel) {
	//int X = x, Y = y, Z = z;
	//const auto& pos = getSectorPos(x, z);
	//
	//std::lock_guard<std::recursive_mutex> lock(m_mutex);
	//if (m_sectors.doesSectorExist(pos)) {
	//	updateMeshes(pos, y / Segment::WIDTH);
	//	updateMeshes(pos, (y + 1) / Segment::WIDTH);
	//	updateMeshes(pos, (y - 1) / Segment::WIDTH);
	//	std::tie(x, y, z) = getVoxelPos(x, y, z);
	//	m_sectors.getSectorAt(pos).setVoxel(x, y, z, voxel);
	//
	//	addToUpdates(X, Y, Z);
	//}
}

Voxel::Element World::getVoxel(int x, int y, int z) const {
	//const auto& pos = getSectorPos(x, z);
	//
	//std::lock_guard<std::recursive_mutex> lock(m_mutex);
	//if (m_sectors.doesSectorExist(pos)) {
	//	std::tie(x, y, z) = getVoxelPos(x, y, z);
	//	return m_sectors.getSectors().at(pos).getVoxel(x, y, z);
	//}
	return Voxel::Element();
}

void World::update(const Camera& camera) {
	m_camPosition = { (int)camera.getPosition().x / Segment::WIDTH, (int)camera.getPosition().z / Segment::WIDTH };
	
	std::lock_guard<std::recursive_mutex> lock(m_mutex);
	m_segments.unloadSegmentIf([&](const Vector3& pos) {
		return pos.x < m_camPosition.x - m_renderDistance || pos.x > m_camPosition.x + m_renderDistance ||
			   pos.z < m_camPosition.z - m_renderDistance || pos.z > m_camPosition.z + m_renderDistance;
	});
}

void World::renderSector(MasterRenderer& renderer, const Frustum& frustum) {
	m_segments.renderSegments(renderer, frustum);
}

void World::makeSector() {
	while (m_running) {
		for (int x = m_camPosition.x - m_renderDistance; x <= m_camPosition.x + m_renderDistance; x++) {
			for (int y = 0; y < 9; y++) {
				for (int z = m_camPosition.z - m_renderDistance; z <= m_camPosition.z + m_renderDistance; z++) {
					//makeEditedMeshes();

					if (!m_segments.doesSegmentExist({ x, y, z })) {
						auto segment = std::make_shared<Segment>();

						for (int X = 0; X < 16; X++) {
							for (int Y = 0; Y < 16; Y++) {
								for (int Z = 0; Z < 16; Z++) {
									segment->setVoxel(X, Y, Z, Voxel::Type::GRASS);
								}
							}
						}

						//m_mapGenerator->generateSector(sector, { x,z });
						std::lock_guard<std::recursive_mutex> lock(m_mutex);
						m_segments.loadSegment({ x, y, z }, segment);
					}
					else {
						m_segments.makeMesh({ x, y, z });
					}
				}
			}
		}
		m_currentRadius++;
		m_currentRadius %= m_renderDistance;
		std::this_thread::sleep_for(std::chrono::microseconds(10));
	}
}

void World::updateVoxels() {
	while (m_running) {
		std::unique_lock<std::recursive_mutex> lock(m_mutex);
		for (auto itr = m_updateList.begin(); itr != m_updateList.end();) {
			int x = itr->x;
			int y = itr->y;
			int z = itr->z;

			if (getVoxel(x, y, z).getUpdateHandler()->update(*this, x, y, z)) {
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
	//std::unique_lock<std::recursive_mutex> lock(m_mutex);
	//for (auto itr = m_regenSectors.begin(); itr != m_regenSectors.end();) {
	//	if (m_sectors.doesSectorExist(*itr)) {
	//		const auto pos = *itr;
	//		lock.unlock();
	//		m_sectors.makeMesh(pos);
	//		lock.lock();
	//		itr = m_regenSectors.erase(itr);
	//	}
	//	else
	//		itr++;
	//}
}

void World::updateMeshes(const VecXZ& pos, std::int16_t y) {
	//if (y > 0) {
	//	m_sectors.getSectorAt(pos).regenMesh(y - 1);
	//}
	//if (y < Sector::HEIGHT - 1) {
	//	m_sectors.getSectorAt(pos).regenMesh(y + 1);
	//}
	//
	//m_sectors.getSectorAt(pos).regenMesh(y);
	//m_sectors.getSectorAt({ pos.x + 1, pos.z     }).regenMesh(y);
	//m_sectors.getSectorAt({ pos.x    , pos.z + 1 }).regenMesh(y);
	//m_sectors.getSectorAt({ pos.x - 1, pos.z     }).regenMesh(y);
	//m_sectors.getSectorAt({ pos.x    , pos.z - 1 }).regenMesh(y);
	//
	//m_regenSectors.emplace(pos);
	//m_regenSectors.insert({pos.x + 1, pos.z     });
	//m_regenSectors.insert({pos.x    , pos.z + 1 });
	//m_regenSectors.insert({pos.x - 1, pos.z     });
	//m_regenSectors.insert({pos.x    , pos.z - 1 });
}

void World::addToUpdates(int x, int y, int z) {
	auto tryAdd = [&](int X, int Y, int Z) {
		if (getVoxel(X, Y, Z).getUpdateHandler()->isUpdatable()) {
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

const VecXZ World::getSectorPos(int x, int z) const {
	return {x / Segment::WIDTH, z / Segment::WIDTH};
}

const std::tuple<int, int, int> World::getVoxelPos(int x, int y, int z) const {
	return std::tuple<int, int, int>(abs(x) % Segment::WIDTH, y, abs(z) % Segment::WIDTH);
}
