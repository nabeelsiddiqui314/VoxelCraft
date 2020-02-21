#pragma once
#include <unordered_map>
#include "Sector.h"
#include <functional>
#include <algorithm>
#include <utility>
#include "../../Math/vecXZ.h"

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

	const SectorHashtable& getSectors() const;
	Sector& getSectorAt(const VecXZ& pos);
private:
	SectorHashtable m_sectors;
};

