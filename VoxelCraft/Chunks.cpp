#include "stdafx.h"
#include "Chunks.h"

void Chunks::setBlock(std::int16_t x, std::int16_t y, std::int16_t z, BlockType id) {
	m_segments[y / Chunks::HEIGHT].setBlock(x, y % Chunks::HEIGHT, z, id);
}

BlockType Chunks::getBlock(std::int16_t x, std::int16_t y, std::int16_t z) const {
	return m_segments[y / Chunks::HEIGHT].getBlock(x, y % Chunks::HEIGHT, z);
}

void Chunks::makeMesh(std::int16_t x, std::int16_t z,
	const Chunks* left, const Chunks* right,
	const Chunks* front, const Chunks* back) {
	for (std::size_t y = HEIGHT - 1; y >= 0; y--) {
		if (!m_segments[y].hasMeshGenerated()) {
			if (y > 0 && y < Chunks::HEIGHT - 1) {
				m_segments[y].makeMesh(x * Segment::WIDTH, y * Segment::WIDTH, z * Segment::WIDTH,
					&getSegment(y), &getSegment(y + 1), &getSegment(y - 1), &left->getSegment(y), 
					&right->getSegment(y), &front->getSegment(y), &back->getSegment(y));
			}
			else if (y > 0) {
				m_segments[y].makeMesh(x * Segment::WIDTH, y * Segment::WIDTH, z * Segment::WIDTH,
					&getSegment(y), nullptr, &getSegment(y - 1), &left->getSegment(y),
					&right->getSegment(y), &front->getSegment(y), &back->getSegment(y));
			}
			else {
				m_segments[y].makeMesh(x * Segment::WIDTH, y * Segment::WIDTH, z * Segment::WIDTH,
					&getSegment(y), &getSegment(y + 1), nullptr, &left->getSegment(y),
					&right->getSegment(y), &front->getSegment(y), &back->getSegment(y));
			}
			
			break;
		}
	}
	for (auto& segment : m_segments) {
		if (!segment.hasMeshGenerated()) {
			m_hasMesh = false;
			return;
		}
	}
	m_hasMesh = true;
}

bool Chunks::hasMesh() const {
	return m_hasMesh;
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