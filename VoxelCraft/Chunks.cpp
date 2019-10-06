#include "stdafx.h"
#include "Chunks.h"

void Chunks::setBlock(std::int16_t x, std::int16_t y, std::int16_t z, BlockType id) {
	m_segments[y / Segment::WIDTH].setBlock(x, y % Segment::WIDTH, z, id);
}

BlockType Chunks::getBlock(std::int16_t x, std::int16_t y, std::int16_t z) const {
	return m_segments[y / Segment::WIDTH].getBlock(x, y % Segment::WIDTH, z);
}

void Chunks::makeMesh(std::int16_t x, std::int16_t z,
	const Chunks* left, const Chunks* right,
	const Chunks* front, const Chunks* back) {
	for (std::size_t y = HEIGHT; y-- > 0;) {
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
		}
	}
}

void Chunks::regenMesh(std::int16_t y) {
	if(m_segments[y].hasMeshGenerated())
		m_segments[y].regenMesh();
}

void Chunks::cleanUp() {
	for (auto& segment : m_segments) {
		segment.cleanBuffers();
	}
}

const Segment& Chunks::getSegment(std::uint8_t index) const {
	return m_segments[index];
}

void Chunks::makeBoxes(const VecXZ& pos) {
	for (std::size_t y = 0; y < Chunks::HEIGHT; y++) {
		m_segments[y].setBoxPosition(glm::vec3(pos.x * Segment::WIDTH, y * Segment::WIDTH, pos.z * Segment::WIDTH));
	}
}

void Chunks::render(MasterRenderer& renderer, const Frustum& frustum) {
	for (auto& segment : m_segments) {
		if (segment.isEmpty())
			continue;

		if (segment.hasMeshGenerated() && !segment.hasModelLoaded()) {
			segment.loadModel();
		}
		if (segment.hasModelLoaded()) {
			if(frustum.isBoxInFrustum(segment.getBox()))
				segment.render(renderer);
		}
	}
}