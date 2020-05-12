#include "Sector.h"
#include "../../Math/vecXZ.h"
#include "../../Math/Frustum.h"

Sector::Sector() {
	m_segments.reserve(HEIGHT);
}

void Sector::setVoxel(int x, int y, int z, Voxel::Type id) {
	m_segments[y / Segment::WIDTH].setVoxel(x, y % Segment::WIDTH, z, id);
}

Voxel::Element Sector::getVoxel(int x, int y, int z) const {
	return m_segments[y / Segment::WIDTH].getVoxel(x, y % Segment::WIDTH, z);
}

void Sector::makeMesh() {
	
}

void Sector::regenMesh(int y) {
	
}

void Sector::cleanUp() {

}

const Segment& Sector::getSegment(std::uint8_t index) const {
	return m_segments[index];
}

Segment& Sector::getSegment(std::uint8_t index) {
	return m_segments[index];
}

void Sector::render(MasterRenderer& renderer, const Frustum& frustum) {
	for (auto& segment : m_segments) {
		
	}
}