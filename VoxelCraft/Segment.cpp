#include "stdafx.h"
#include "Segment.h"

Segment::Segment() : m_opaqueCount(0), m_voidCount(WIDTH * WIDTH * WIDTH) {
	m_blocks.fill(BlockType::VOID);
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
	const Segment* chunk,
	const Segment* top, const Segment* bottom,
	const Segment* left, const Segment* right,
	const Segment* front, const Segment* back) {
	cleanUp();
	SegmentMeshMaker(m_meshTypes, originX, originY, originZ, chunk, top, bottom, left, right, front, back);
	m_hasMeshGenerated = true;
}

void Segment::regenMesh() {
	m_hasMeshGenerated = false;
}

void Segment::loadModel() {
	m_meshTypes.solid.loadMeshToModel();
	m_meshTypes.water.loadMeshToModel();
	m_hasLoadedModel = true;
}

void Segment::cleanUp() {
	m_meshTypes.solid.cleanUp();
	m_meshTypes.water.cleanUp();
}

void Segment::render(MasterRenderer& renderer) {
	renderer.addChunk(m_meshTypes);
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