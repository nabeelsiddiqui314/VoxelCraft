#include "stdafx.h"
#include "SegmentBounds.h"

SegmentBounds& SegmentBounds::getInstance() {
	static SegmentBounds instance;
	return instance;
}

Segment* SegmentBounds::getSegment(Segment& segment, int x, int y, int z) {
	int dx = getOffsetOrdinate(x);
	int dy = getOffsetOrdinate(y);
	int dz = getOffsetOrdinate(z);

	return segment.getRelativeSegment(dx, dy, dz);
}

const Segment* SegmentBounds::getConstSegment(const Segment& segment, int x, int y, int z) const {
	int dx = getOffsetOrdinate(x);
	int dy = getOffsetOrdinate(y);
	int dz = getOffsetOrdinate(z);

	return segment.getRelativeSegment(dx, dy, dz);
}

Voxel::Element SegmentBounds::getVoxel(const Segment& segment, int x, int y, int z) const {
	auto* segmentPtr = getConstSegment(segment, x, y, z);

	if (!segmentPtr) {
		return Voxel::Type::VOID;
	}

	int X = getLocalOrdinate(x);
	int Y = getLocalOrdinate(y);
	int Z = getLocalOrdinate(z);

	return segmentPtr->getVoxel(X, Y, Z);
}

int SegmentBounds::getOffsetOrdinate(int local) const {
	if (local < 0) {
		return -1;
	}
	else if (local >= Segment::WIDTH) {
		return 1;
	}
	return 0;
}

int SegmentBounds::getLocalOrdinate(int local) const {
	if (local < 0) {
		return Segment::WIDTH - abs(local);
	}
	else if (local >= Segment::WIDTH) {
		return local % Segment::WIDTH;
	}
	return local;
}