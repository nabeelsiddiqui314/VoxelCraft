#pragma once
#include <unordered_map>
#include "vecXZ.h"
#include "Sector.h"
#include <functional>
#include <algorithm>
#include <utility>

class SectorManager
{
private:
	typedef std::unordered_map<VecXZ, Sector> SectorHashtable;
public:
	SectorManager() = default;
	~SectorManager();
public:
	void loadSector(const VecXZ& pos, const Sector& sectors);
	void unloadSector(const std::function<bool(const VecXZ& pos)>& cond);

	bool doesSectorExist(const VecXZ& pos) const;

	void makeMesh(const VecXZ& pos);

	const SectorHashtable& getHashTable() const;
	Sector& getSectorAt(const VecXZ& pos);
private:
	SectorHashtable m_sectors;
};

