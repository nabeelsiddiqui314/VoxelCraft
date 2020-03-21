#include "SegmentGenerationTask.h"
#include "../Segmentmanager.h"

SegmentGenerationTask::SegmentGenerationTask(const Vector3& pos) 
	: m_position(pos),
      m_segment(pos.x, pos.y, pos.z) {}

void SegmentGenerationTask::execute() {
	for (int x = 0; x < Segment::WIDTH; x++) {
		for (int y = 0; y < Segment::WIDTH; y++) {
			for (int z = 0; z < Segment::WIDTH; z++) {
				m_segment.setVoxel(x, y, z, Voxel::Type::DIRT);
			}
		}
	}
}

std::shared_ptr<ITaskProduct> SegmentGenerationTask::getProduct() {
	return std::make_shared<SegmentProduct>(m_segment);
}

SegmentProduct::SegmentProduct(Segment& segment) 
	: m_segment(segment) {}

void SegmentProduct::sendProduct(SegmentManager& manager) {
	manager.addSegment(m_segment.getWorldPosition(), m_segment);
}