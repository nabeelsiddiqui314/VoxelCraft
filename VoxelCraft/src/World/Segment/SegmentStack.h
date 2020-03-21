#pragma once
#include <cstdint>
#include <vector>
#include "Segment.h"

class SegmentStack
{
public:
	SegmentStack();
public:
	void setVoxel(int x, int y, int z, Voxel::Type id);
	Voxel::Element getVoxel(int x, int y, int z) const;

	std::vector<Segment>& getSegments();
public:
	static constexpr std::int16_t HEIGHT = 16;
private:
	std::vector<Segment> m_segments;
};

