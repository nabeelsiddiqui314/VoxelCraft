#pragma once
#include <memory>
#include <thread>
#include <mutex>
#include <unordered_set>
#include "../CppUtil/NonCopyable.h"
#include "Segment/SegmentManager.h"
#include "../Math/vecXZ.h"
#include "Voxel/VoxelElement.h"

class Camera;
class MapGenerator;
class MasterRenderer;
class Frustum;

class World : public NonCopyable
{
public:
	World();
	~World();
public:
	void setVoxel(int x, int y, int z, Voxel::Type voxel);
	Voxel::Element getVoxel(int x, int y, int z) const;

	void update(const Camera& camera);
	void renderSector(MasterRenderer& renderer, const Frustum& frustum);
private:
	void makeSector();
	void updateVoxels();

	void makeEditedMeshes();
	void updateMeshes(const VecXZ& pos, std::int16_t y);
	void addToUpdates(int x, int y, int z);

	const VecXZ getSectorPos(int x, int z) const;
	const std::tuple<int, int, int> getVoxelPos(int x, int y, int z) const;
private:
	SegmentManager m_segments;
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