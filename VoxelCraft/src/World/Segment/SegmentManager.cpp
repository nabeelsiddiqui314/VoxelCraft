#include "SegmentManager.h"
#include "Generation/SegmentGenerationTask.h"
#include "Generation/SegmentMeshingTask.h"

SegmentManager::~SegmentManager() {
	m_segments.clear();
}

void SegmentManager::loadSegment(const Vector3& pos) {
	m_segmentGenerator.orderTask<SegmentGenerationTask>(pos);
}

void SegmentManager::unloadSegment(const std::function<bool(const Vector3& pos)>& cond) {
	//for (auto itr = m_segments.begin(); itr != m_segments.end();) {
	//	if (cond(itr->first)) {
	//		m_segments[itr->first].cleanUp();
	//		itr = m_segments.erase(itr);
	//	}
	//	else
	//		itr++;
	//}
}

void SegmentManager::addSegment(const Vector3& pos, Segment& segment) {
	m_segments.insert(std::make_pair(pos, RenderableSegment(segment)));

	auto setAsNeighborTo = [&](int x, int y, int z, const Segment::Neighbor& neighbor) {
		Vector3 neighborPos = { pos.x + x, pos.y + y, pos.z + z };
		if (doesSegmentExist(neighborPos)) {
			m_segments.at(neighborPos).segment.setNeighborSegment(neighbor, &segment);
		}
	};

	setAsNeighborTo(1, 0, 0, Segment::Neighbor::LEFT);
	setAsNeighborTo(-1, 0, 0, Segment::Neighbor::RIGHT);
	setAsNeighborTo(0, 1, 0, Segment::Neighbor::BOTTOM);
	setAsNeighborTo(0, -1, 0, Segment::Neighbor::TOP);
	setAsNeighborTo(0, 0, 1, Segment::Neighbor::BACK);
	setAsNeighborTo(0, 0, -1, Segment::Neighbor::FRONT);
}

void SegmentManager::addMesh(const Vector3& pos, const SegmentMeshes& meshes) {
	m_segments.at(pos).loadMeshes(meshes);
}

bool SegmentManager::doesSegmentExist(const Vector3& pos) const {
	return m_segments.find(pos) != m_segments.end();
}

void SegmentManager::loadGeneratedSegments() {
	for (auto& segment : m_segments) {
		if (!segment.second.hasMeshGenerated()) {
			if (segment.second.segment.getNeighborSegment(Segment::Neighbor::FRONT) &&
				segment.second.segment.getNeighborSegment(Segment::Neighbor::BACK) && 
				segment.second.segment.getNeighborSegment(Segment::Neighbor::LEFT) && 
				segment.second.segment.getNeighborSegment(Segment::Neighbor::RIGHT)) {
				m_segmentGenerator.orderTask<SegmentMeshingTask>(segment.second.segment);
			}
		}
	}

	m_segmentGenerator.recieveProducedData(*this);
}

void SegmentManager::render(MasterRenderer& renderer, const Frustum& frustum) {
	for (auto& segment : m_segments) {
		segment.second.render(renderer, frustum);
	}
}