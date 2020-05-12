#include "RenderableSegment.h"
#include "Segment.h"
#include "../../Math/Frustum.h"
#include "../../Renderer/MasterRenderer.h"
#include "SegmentMeshGenerator.h"

RenderableSegment::RenderableSegment(std::shared_ptr<Segment> segment, const Vector3& worldPos)
	: m_segment(segment), m_worldPos(worldPos) {
	m_box.position = { worldPos.x * Segment::WIDTH, worldPos.y * Segment::WIDTH, worldPos.z * Segment::WIDTH };
	m_box.dimensions = {Segment::WIDTH, Segment::WIDTH, Segment::WIDTH };
}

void RenderableSegment::generateMesh() {
	if (!m_hasMeshGenerated) {
		cleanUp();

		SegmentMeshGenerator::generateMesh(m_meshTypes, m_worldPos, *m_segment);
		m_hasMeshGenerated = true;
		m_hasLoadedModel = false;
	}
}

void RenderableSegment::render(MasterRenderer& renderer, const Frustum& frustum) {
	if (!m_segment->isEmpty()) {
		if (m_hasMeshGenerated && !m_hasLoadedModel) {
			
			deleteBuffers();

			m_meshTypes.solid.loadMeshToModel();
			m_meshTypes.liquid.loadMeshToModel();
			m_meshTypes.flora.loadMeshToModel();
			m_hasLoadedModel = true;
		}
		if (m_hasLoadedModel) {
			if (frustum.isBoxInFrustum(m_box))
				renderer.addSector(m_meshTypes);
		}
	}
}

void RenderableSegment::deleteBuffers() {
	if (m_meshTypes.solid.model.hasData())
		m_meshTypes.solid.model.deleteBuffers();

	if (m_meshTypes.liquid.model.hasData())
		m_meshTypes.liquid.model.deleteBuffers();

	if (m_meshTypes.flora.model.hasData())
		m_meshTypes.flora.model.deleteBuffers();
}

void RenderableSegment::cleanUp() {
	m_meshTypes.solid.cleanUp();
	m_meshTypes.liquid.cleanUp();
	m_meshTypes.flora.cleanUp();
}

std::shared_ptr<Segment> RenderableSegment::getSegment() const {
	return m_segment;
}
