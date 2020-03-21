#include "RenderableSegment.h"
#include "../../Renderer/MasterRenderer.h"
#include "../../Math/Frustum.h"

RenderableSegment::RenderableSegment(Segment& segment) 
	: segment(segment) {

	m_boundingBox.position = { segment.getWorldPosition().x * Segment::WIDTH,
		segment.getWorldPosition().y * Segment::WIDTH,
		segment.getWorldPosition().z * Segment::WIDTH };
	m_boundingBox.dimensions = { Segment::WIDTH , Segment::WIDTH , Segment::WIDTH };
}

void RenderableSegment::loadMeshes(const SegmentMeshes& meshes) {
	cleanUpMeshes();
	m_meshes = meshes;
	m_hasMeshGenerated = true;
	m_hasModelLoaded = false;
}

void RenderableSegment::loadModels() {
	cleanUpModels();
	m_models.solid.addMesh(m_meshes.solid.getMesh());
	m_models.liquid.addMesh(m_meshes.liquid.getMesh());
	m_models.flora.addMesh(m_meshes.flora.getMesh());
	m_hasModelLoaded = true;
}

void RenderableSegment::remesh() {
	m_hasModelLoaded = true;
	m_hasMeshGenerated = false;
}

void RenderableSegment::cleanUp() {
	cleanUpMeshes();
	cleanUpModels();
}

bool RenderableSegment::hasMeshGenerated() {
	return m_hasMeshGenerated;
}

void RenderableSegment::render(MasterRenderer& renderer, const Frustum& frustum) {
	if (!segment.isEmpty()) {
		if (m_hasMeshGenerated && !m_hasModelLoaded) {
			loadModels();
		}
		if (m_hasModelLoaded) {
			if (frustum.isBoxInFrustum(m_boundingBox))
				renderer.addSegment(m_models);
		}
	}
}

void RenderableSegment::cleanUpMeshes() {
	m_meshes.solid.cleanUp();
	m_meshes.liquid.cleanUp();
	m_meshes.flora.cleanUp();
}

void RenderableSegment::cleanUpModels() {
	if (m_models.solid.hasData())
		m_models.solid.deleteBuffers();

	if (m_models.liquid.hasData())
		m_models.liquid.deleteBuffers();

	if (m_models.flora.hasData())
		m_models.flora.deleteBuffers();
}
