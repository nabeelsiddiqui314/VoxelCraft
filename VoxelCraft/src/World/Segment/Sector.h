#pragma once
#include <cstdint>
#include <vector>
#include "Segment.h"

class MasterRenderer;
class Frustum;

class Sector
{
public:
	Sector();
public:

	void setVoxel(int x, int y, int z, Voxel::Type id);
	Voxel::Element getVoxel(int x, int y, int z) const;

	void makeMesh();
	void regenMesh(int y);
	void cleanUp();

	const Segment& getSegment(std::uint8_t index) const;
	Segment& getSegment(std::uint8_t index);

	void render(MasterRenderer& renderer, const Frustum& frustum);
public:
	static constexpr std::int16_t HEIGHT = 16;
private:
	std::vector<Segment> m_segments;
};

