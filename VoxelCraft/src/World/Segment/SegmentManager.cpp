#include "SegmentManager.h"
#include "Segment.h"

SegmentManager::~SegmentManager() {
	m_segments.clear();
}

void SegmentManager::loadSegment(const Vector3& pos, std::shared_ptr<Segment> segment) {
	RenderableSegment newSegment(segment, pos);
	m_segments.emplace(std::make_pair(pos, newSegment));
	
	auto makeNeighbors = [&](int x, int y, int z, const Segment::NeighborPosition& NeighborPos, const Segment::NeighborPosition& oppositePos) {
		Vector3 neighborWorldPosition = { pos.x + x, pos.y + y, pos.z + z };
		if (doesSegmentExist(neighborWorldPosition)) {
			m_segments.at(pos).getSegment()->setNeighbor(m_segments.at(neighborWorldPosition).getSegment(), NeighborPos);
			m_segments.at(neighborWorldPosition).getSegment()->setNeighbor(m_segments.at(pos).getSegment(), oppositePos);
		}
	};

	makeNeighbors( 1,  0,  0, Segment::NeighborPosition::RIGHT, Segment::NeighborPosition::LEFT);
	makeNeighbors(-1,  0,  0, Segment::NeighborPosition::LEFT, Segment::NeighborPosition::RIGHT);

	makeNeighbors( 0,  1,  0, Segment::NeighborPosition::TOP, Segment::NeighborPosition::BOTTTOM);
	makeNeighbors( 0, -1,  0, Segment::NeighborPosition::BOTTTOM, Segment::NeighborPosition::TOP);

	makeNeighbors( 0,  0,  1, Segment::NeighborPosition::FRONT, Segment::NeighborPosition::BACK);
	makeNeighbors( 0,  0, -1, Segment::NeighborPosition::BACK, Segment::NeighborPosition::FRONT);
}

void SegmentManager::unloadSegmentIf(const RemovalTest& callback) {
	for (auto itr = m_segments.begin(); itr != m_segments.end();) {
		if (callback(itr->first)) {
			itr = m_segments.erase(itr);
		}
		else {
			itr++;
		}
	}
}

bool SegmentManager::doesSegmentExist(const Vector3& pos) const {
	return m_segments.find(pos) != m_segments.end();
}

void SegmentManager::makeMesh(const Vector3& pos) {
	m_segments.at(pos).generateMesh();
}

void SegmentManager::renderSegments(MasterRenderer& renderer, const Frustum& frustum) {
	for (auto& segment : m_segments) {
		segment.second.render(renderer, frustum);
	}
}