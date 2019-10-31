#pragma once
#include "SegmentMeshMaker.h"
#include "Segment.h"
#include "vecXZ.h"

class Sector
{
public:
	void setVoxel(std::int16_t x, std::int16_t y, std::int16_t z, Voxel::Type id);
	Voxel::Element getVoxel(std::int16_t x, std::int16_t y, std::int16_t z) const;

	void makeMesh(std::int16_t x, std::int16_t z,
		const Sector* left, const Sector* right,
		const Sector* front, const Sector* back);
	void regenMesh(std::int16_t y);
	void cleanUp();

	const Segment& getSegment(std::uint8_t index) const;

	void makeBoxes(const VecXZ& pos);
	void render(MasterRenderer& renderer, const Frustum& frustum);
public:
	static constexpr std::int16_t HEIGHT = 16;
private:
	std::array<Segment, HEIGHT> m_segments;
};

