#pragma once
#include "Segment.h"

class SegmentBounds
{
private:
	SegmentBounds() = default;
	~SegmentBounds() = default;
public:
	static SegmentBounds& getInstance();
public:
	const Segment* getSegment(const Segment& segment, int x, int y, int z) const;
	Voxel::Element getVoxel(const Segment& segment, int x, int y, int z) const;
private:
	int getOffsetOrdinate(int local) const;
	int getLocalOrdinate(int local) const;
};

