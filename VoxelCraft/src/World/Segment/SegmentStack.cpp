#include "SegmentStack.h"
#include "../../Math/Frustum.h"

SegmentStack::SegmentStack() {
	m_segments.reserve(HEIGHT);
}

void SegmentStack::setVoxel(int x, int y, int z, Voxel::Type id) {
	m_segments[y / Segment::WIDTH].setVoxel(x, y % Segment::WIDTH, z, id);
}

Voxel::Element SegmentStack::getVoxel(int x, int y, int z) const {
	return m_segments[y / Segment::WIDTH].getVoxel(x, y % Segment::WIDTH, z);
}

std::vector<Segment>& SegmentStack::getSegments() {
	return m_segments;
}