#pragma once
#include <unordered_map>
#include "vecXZ.h"
#include "Sector.h"
#include <functional>
#include <algorithm>
#include <utility>

class SectorManager
{
public:
	SectorManager() = default;
	~SectorManager();
public:
	void loadSector(const VecXZ& pos, const Sector& sectors);
	void unloadSector(const std::function<bool(const VecXZ& pos)>& cond);

	bool doesSectorExist(const VecXZ& pos) const;

	void setBlock(const VecXZ& pos, std::int16_t x, std::int16_t y, std::int16_t z, BlockType id);
	BlockType getBlock(const VecXZ& pos, std::int16_t x, std::int16_t y, std::int16_t z) const;

	void makeMesh(const VecXZ& pos);
	const Sector& getSectorAt(const VecXZ& pos) const;
	void regenMesh(const VecXZ& pos, std::int16_t y);

	void render(const VecXZ& pos, MasterRenderer& renderer, const Frustum& frustum);
private:
	std::unordered_map<VecXZ, Sector> m_sectors;
};

