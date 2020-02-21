#include "SectorManager.h"
#include "../../Math/vecXZ.h"

SectorManager::~SectorManager() {
	m_sectors.clear();
}

void SectorManager::loadSector(const VecXZ& pos, const Sector& sectors) {
	m_sectors.emplace(std::make_pair(pos, sectors));
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

void SectorManager::makeMesh(const VecXZ& pos) {
	if (doesSectorExist({ pos.x - 1, pos.z }) && 
		doesSectorExist({ pos.x + 1, pos.z }) && 
		doesSectorExist({ pos.x,     pos.z + 1}) &&
		doesSectorExist({ pos.x,     pos.z - 1})) {
		m_sectors[pos].makeMesh();
	}
}

const SectorManager::SectorHashtable& SectorManager::getSectors() const {
	return m_sectors;
}

Sector& SectorManager::getSectorAt(const VecXZ& pos) {
	return m_sectors.at(pos);
}