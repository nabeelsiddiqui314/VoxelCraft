#include "stdafx.h"
#include "Segment.h"
#include "SectorManager.h"

Segment::Segment(int x, int y, int z, SectorManager& sectors) 
	: m_opaqueCount(0),
	  m_voidCount(WIDTH * WIDTH * WIDTH),
      m_sectors(sectors),
      m_worldPosition(x, y, z) {
	m_box.dimensions = {Segment::WIDTH, Segment::WIDTH, Segment::WIDTH};
}

void Segment::setVoxel(std::int16_t x, std::int16_t y, std::int16_t z, Voxel::Type id) {
	Voxel::Element ID = id;

	if (!getVoxel(x, y, z).getInfo().opaque && ID.getInfo().opaque)
		m_opaqueCount++;
	else if (getVoxel(x, y, z).getInfo().opaque && !ID.getInfo().opaque)
		m_opaqueCount--;

	if (getVoxel(x, y, z) != Voxel::Type::VOID && ID == Voxel::Type::VOID)
		m_voidCount++;
	else if (getVoxel(x, y, z) == Voxel::Type::VOID && ID != Voxel::Type::VOID)
		m_voidCount--;

	m_voxels[x + WIDTH * (y + WIDTH * z)] = ID;
}

Voxel::Element Segment::getVoxel(std::int16_t x, std::int16_t y, std::int16_t z) const {
	return m_voxels[x + WIDTH * (y + WIDTH * z)];
}

void Segment::makeMesh() {
	cleanUp();
	SegmentMeshMaker(m_meshTypes, *this);
	m_hasMeshGenerated = true;
	m_hasLoadedModel = false;
}

const Segment* Segment::getRelativeSegment(int x, int y, int z) const {
	x += m_worldPosition.x;
	y += m_worldPosition.y;
	z += m_worldPosition.z;

	if (y >= 0 && y < Sector::HEIGHT) {
		return &m_sectors.getSectors().at({ x, z }).getSegment(y);
	}
	
	return nullptr;
}

const Vector3& Segment::getWorldPosition() const {
	return m_worldPosition;
}

void Segment::regenMesh() {
	m_hasLoadedModel = true;
	m_hasMeshGenerated = false;
}

void Segment::loadModel() {
	cleanBuffers();
	m_meshTypes.solid.loadMeshToModel();
	m_meshTypes.liquid.loadMeshToModel();
	m_meshTypes.flora.loadMeshToModel();
	m_hasLoadedModel = true;
}

void Segment::cleanUp() {
	m_meshTypes.solid.cleanUp();
	m_meshTypes.liquid.cleanUp();
	m_meshTypes.flora.cleanUp();
}

void Segment::cleanBuffers() {
	if(m_meshTypes.solid.model.hasData())
		m_meshTypes.solid.model.deleteBuffers();

	if(m_meshTypes.liquid.model.hasData())
		m_meshTypes.liquid.model.deleteBuffers();

	if (m_meshTypes.flora.model.hasData())
		m_meshTypes.flora.model.deleteBuffers();
}

void Segment::render(MasterRenderer& renderer) {
	renderer.addSector(m_meshTypes);
}

void Segment::setBoxPosition(const glm::vec3& pos) {
	m_box.position = pos;
}

const AABB& Segment::getBox() const {
	return m_box;
}

bool Segment::isAllOpaque() const {
	return m_opaqueCount == WIDTH * WIDTH * WIDTH;
}

bool Segment::isEmpty() const {
	return m_voidCount == WIDTH * WIDTH * WIDTH;
}

bool Segment::hasMeshGenerated() const {
	return m_hasMeshGenerated;
}

bool Segment::hasModelLoaded() const {
	return m_hasLoadedModel;
}