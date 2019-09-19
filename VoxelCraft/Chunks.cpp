#include "stdafx.h"
#include "Chunks.h"

void Chunks::setBlock(std::int16_t x, std::int16_t y, std::int16_t z, BlockType id) {
	m_segments[y / Chunks::HEIGHT].setBlock(x, y % Chunks::HEIGHT, z, id);
}

BlockType Chunks::getBlock(std::int16_t x, std::int16_t y, std::int16_t z) const {
	return m_segments[y / Chunks::HEIGHT].getBlock(x, y % Chunks::HEIGHT, z);
}

bool Chunks::createMesh(std::int16_t originX, std::int16_t originZ,
	const Chunks* left, const Chunks* right,
	const Chunks* front, const Chunks* back) {
	for (int i = 0; i < m_segments.size(); i++) {
		if (!m_segments[i].hasMeshGenerated()) {
			m_segments[i].createMesh(originX, originZ, ((i != HEIGHT - 1) ? &m_segments[i + 1] : nullptr),
				((i != 0) ? &m_segments[i - 1] : nullptr), 
				&left->getSegment(i), &right->getSegment(i),
				&front->getSegment(i), &back->getSegment(i));
			if (m_segments[i].getModels().solid.model.has_value()) {
				return true;
			}
		}
	}
	return false;
}

const Segment& Chunks::getSegment(std::uint8_t index) const {
	return m_segments[index];
}

void Chunks::render(MasterRenderer& renderer) {
	for (auto& segment : m_segments) {
		segment.render(renderer);
	}
}