#include "stdafx.h"
#include "Chunks.h"

void Chunks::setBlock(std::int16_t x, std::int16_t y, std::int16_t z, BlockType id) {
	m_segments[y / Chunks::HEIGHT].setBlock(x, y % Chunks::HEIGHT, z, id);
}

BlockType Chunks::getBlock(std::int16_t x, std::int16_t y, std::int16_t z) const {
	return m_segments[y / Chunks::HEIGHT].getBlock(x, y % Chunks::HEIGHT, z);
}

void Chunks::setMesh(const Mesh& mesh, std::int16_t y) {
	if (!hasMesh(y))
		m_segments[y].setMesh(mesh);
}

bool Chunks::hasMesh(std::int16_t y) const {
	return m_segments[y].hasMeshGenerated();
}

const Segment& Chunks::getSegment(std::uint8_t index) const {
	return m_segments[index];
}

void Chunks::render(MasterRenderer& renderer) {
	for (auto& segment : m_segments) {
		if (segment.hasMeshGenerated()) {
			segment.loadModel();
			segment.render(renderer);
		}
	}
}