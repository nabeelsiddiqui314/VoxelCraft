#include "stdafx.h"
#include "Sector.h"
#include "SectorManager.h"

Sector::Sector() {
	m_segments.reserve(HEIGHT);
}

void Sector::fillSegments(int x, int z, SectorManager& sectors) {
	for (std::size_t y = 0; y < HEIGHT; y++) {
		m_segments.emplace_back(x, y, z, sectors);
	}
}

void Sector::setVoxel(std::int16_t x, std::int16_t y, std::int16_t z, Voxel::Type id) {
	m_segments[y / Segment::WIDTH].setVoxel(x, y % Segment::WIDTH, z, id);
}

Voxel::Element Sector::getVoxel(std::int16_t x, std::int16_t y, std::int16_t z) const {
	return m_segments[y / Segment::WIDTH].getVoxel(x, y % Segment::WIDTH, z);
}

void Sector::makeMesh() {
	for (std::size_t y = HEIGHT; y-- > 0;) {
		if (!m_segments[y].hasMeshGenerated()) {
			m_segments[y].makeMesh();
		}
	}
}

void Sector::regenMesh(std::int16_t y) {
	if(m_segments[y].hasMeshGenerated())
		m_segments[y].regenMesh();
}

void Sector::cleanUp() {
	for (auto& segment : m_segments) {
		segment.cleanBuffers();
	}
}

const Segment& Sector::getSegment(std::uint8_t index) const {
	return m_segments[index];
}

void Sector::makeBoxes(const VecXZ& pos) {
	for (std::size_t y = 0; y < Sector::HEIGHT; y++) {
		m_segments[y].setBoxPosition(glm::vec3(pos.x * Segment::WIDTH, y * Segment::WIDTH, pos.z * Segment::WIDTH));
	}
}

void Sector::render(MasterRenderer& renderer, const Frustum& frustum) {
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