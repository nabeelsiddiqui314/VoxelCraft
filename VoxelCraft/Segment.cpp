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

void Segment::setMesh(const Mesh& mesh) {
	m_mesh = mesh;
	m_hasMeshGenerated = true;
}

void Segment::loadModel() {
	if (!m_mesh.vertices.empty()) {
		m_model.addMesh(m_mesh);

		m_mesh.vertices.clear();
		m_mesh.indices.clear();
		m_mesh.textureCoords.clear();

		m_mesh.vertices.shrink_to_fit();
		m_mesh.indices.shrink_to_fit();
		m_mesh.textureCoords.shrink_to_fit();
	}
}

void Segment::render(MasterRenderer& renderer) {
	renderer.addChunk(m_model);
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