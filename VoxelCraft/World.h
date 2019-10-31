#pragma once
#include "SectorManager.h"
#include "FlatGenerator.h"
#include "OverworldGenerator.h"
#include "MasterRenderer.h"
#include "vector3.h"
#include <memory>
#include <thread>
#include <mutex>
#include <unordered_set>

class World : public NonCopyable
{
public:
	World();
	~World();
public:
	void setVoxel(std::int64_t x, std::int64_t y, std::int64_t z, Voxel::Type voxel);
	Voxel::Element getVoxel(std::int64_t x, std::int64_t y, std::int64_t z) const;

	void update(const Camera& camera);
	void renderSector(MasterRenderer& renderer, const Frustum& frustum);
private:
	void makeSector();
	void updateVoxels();

	void makeEditedMeshes();
	void updateMeshes(const VecXZ& pos, std::int16_t y);
	void addToUpdates(int x, int y, int z);

	const VecXZ getSectorPos(std::int64_t x, std::int64_t z) const;
	const std::tuple<int, int, int> getVoxelPos(std::int64_t x, std::int64_t y, std::int64_t z) const;
private:
	SectorManager m_sectors;
	std::unordered_set<VecXZ> m_regenSectors;
	std::unordered_set<Vector3> m_updateList;
	VecXZ m_camPosition;
	std::unique_ptr<MapGenerator> m_mapGenerator;
	const int m_renderDistance;
	std::vector<std::thread> m_threads;
	mutable std::recursive_mutex m_mutex;
	bool m_running = true;
	int m_currentRadius = 0;
};