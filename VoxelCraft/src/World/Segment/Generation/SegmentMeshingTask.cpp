#include "SegmentMeshingTask.h"
#include "SegmentMeshGenerator.h"
#include "../SegmentManager.h"

SegmentMeshingTask::SegmentMeshingTask(const Segment& segment)
 : m_segment(segment) {}

void SegmentMeshingTask::execute() {
	m_meshes = generateMesh(m_segment);
}

std::shared_ptr<ITaskProduct> SegmentMeshingTask::getProduct() {
	return std::make_shared<MeshProduct>(m_segment, m_meshes);
}

MeshProduct::MeshProduct(const Segment& segment, const SegmentMeshes& meshes) 
	: m_segment(segment), m_meshes(meshes) {}

void MeshProduct::sendProduct(SegmentManager& manager) {
	manager.addMesh(m_segment.getWorldPosition(), m_meshes);
}