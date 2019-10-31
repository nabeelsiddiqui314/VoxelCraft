#include "stdafx.h"
#include "SectorManager.h"

SectorManager::~SectorManager() {
	m_sectors.clear();
}

void SectorManager::loadSector(const VecXZ& pos, const Sector& sectors) {
	m_sectors.emplace(std::make_pair(pos, sectors));
	m_sectors[pos].makeBoxes(pos);
}

void SectorManager::unloadSector(const std::function<bool(const VecXZ& pos)>& cond) {
	for (auto itr = m_sectors.begin(); itr != m_sectors.end();) {
		if (cond(itr->first)) {
			m_sectors[itr->first].cleanUp();
			itr = m_sectors.erase(itr);
		}
		else
			itr++;
	}
}

bool SectorManager::doesSectorExist(const VecXZ& pos) const {
	return m_sectors.find(pos) != m_sectors.end();
}

void SectorManager::setBlock(const VecXZ& pos, std::int16_t x, std::int16_t y, std::int16_t z, BlockType id) {
	m_sectors[pos].setBlock(x, y, z, id);
}

BlockType SectorManager::getBlock(const VecXZ& pos, std::int16_t x, std::int16_t y, std::int16_t z) const {
	return m_sectors.at(pos).getBlock(x, y, z);
}

void SectorManager::makeMesh(const VecXZ& pos) {
	if (doesSectorExist({ pos.x - 1, pos.z }) && 
		doesSectorExist({ pos.x + 1, pos.z }) && 
		doesSectorExist({ pos.x,     pos.z + 1}) &&
		doesSectorExist({ pos.x,     pos.z - 1})) {
		m_sectors[pos].makeMesh(pos.x, pos.z, &m_sectors[{pos.x - 1, pos.z}], &m_sectors[{pos.x + 1, pos.z}],
			&m_sectors[{pos.x, pos.z + 1}], &m_sectors[{pos.x, pos.z - 1}]);
	}
}

const Sector& SectorManager::getSectorAt(const VecXZ& pos) const {
	return m_sectors.at(pos);
}

void SectorManager::regenMesh(const VecXZ& pos, std::int16_t y) {
	m_sectors[pos].regenMesh(y);
}

void SectorManager::render(const VecXZ& pos, MasterRenderer& renderer, const Frustum& frustum) {
	m_sectors[pos].render(renderer, frustum);
}
