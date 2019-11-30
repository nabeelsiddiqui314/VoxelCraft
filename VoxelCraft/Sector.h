#pragma once
#include "SegmentMeshMaker.h"
#include "Segment.h"
#include "vecXZ.h"

class Sector
{
public:
	Sector();
public:
	void fillSegments(int x, int z, SectorManager& sectors);

	void setVoxel(std::int16_t x, std::int16_t y, std::int16_t z, Voxel::Type id);
	Voxel::Element getVoxel(std::int16_t x, std::int16_t y, std::int16_t z) const;

	void makeMesh();
	void regenMesh(std::int16_t y);
	void cleanUp();

	const Segment& getSegment(std::uint8_t index) const;

	void makeBoxes(const VecXZ& pos);
	void render(MasterRenderer& renderer, const Frustum& frustum);
public:
	static constexpr std::int16_t HEIGHT = 16;
private:
	std::vector<Segment> m_segments;
};

