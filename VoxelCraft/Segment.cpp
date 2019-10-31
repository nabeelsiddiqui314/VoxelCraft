#include "stdafx.h"
#include "Segment.h"

Segment::Segment() : m_opaqueCount(0), m_voidCount(WIDTH * WIDTH * WIDTH) {
	m_blocks.fill(BlockType::VOID);
	m_box.dimensions = {Segment::WIDTH, Segment::WIDTH, Segment::WIDTH};
}

void Segment::setBlock(std::int16_t x, std::int16_t y, std::int16_t z, BlockType id) {
	if (!BlockCodex::getBlockData(getBlock(x, y, z)).opaque && BlockCodex::getBlockData(id).opaque)
		m_opaqueCount++;
	else if (BlockCodex::getBlockData(getBlock(x, y, z)).opaque && !BlockCodex::getBlockData(id).opaque)
		m_opaqueCount--;

	if (getBlock(x, y, z) != BlockType::VOID && id == BlockType::VOID)
		m_voidCount++;
	else if (getBlock(x, y, z) == BlockType::VOID && id != BlockType::VOID)
		m_voidCount--;

	m_blocks[x + WIDTH * (y + WIDTH * z)] = id;
}

BlockType Segment::getBlock(std::int16_t x, std::int16_t y, std::int16_t z) const {
	return m_blocks[x + WIDTH * (y + WIDTH * z)];
}

void Segment::makeMesh(std::int16_t originX, std::int16_t originY, std::int16_t originZ,
	const Segment* sector,
	const Segment* top, const Segment* bottom,
	const Segment* left, const Segment* right,
	const Segment* front, const Segment* back) {
	cleanUp();
	SegmentMeshMaker(m_meshTypes, originX, originY, originZ, sector, top, bottom, left, right, front, back);
	m_hasMeshGenerated = true;
	m_hasLoadedModel = false;
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