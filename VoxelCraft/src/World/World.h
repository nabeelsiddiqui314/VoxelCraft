#pragma once
#include <memory>
#include <thread>
#include <mutex>
#include <unordered_set>
#include "../CppUtil/NonCopyable.h"
#include "Segment/SegmentManager.h"

class Camera;
class MapGenerator;

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

	const std::tuple<int, int, int> getVoxelPos(int x, int y, int z) const;
private:
	SegmentManager m_segments;
	Vector3 m_camPosition;
	const int m_renderDistance;
	int m_currentRadius = 0;
};