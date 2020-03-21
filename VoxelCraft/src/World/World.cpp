#include "World.h"
#include "Generation/Map/OverworldGenerator.h"
#include "../OGL/Util/Camera.h"
#include "Segment/SegmentStack.h"

World::World() : m_renderDistance(16) {
	
}

World::~World() {
	
}

void World::setVoxel(int x, int y, int z, Voxel::Type voxel) {
	
}

Voxel::Element World::getVoxel(int x, int y, int z) const {
	return Voxel::Element();
}

void World::update(const Camera& camera) {
	for (int y = 16; y > 0; y--) {
		for (int x = -16; x < 16; x++) {
			for (int z = -16; z < 16; z++) {
				m_segments.loadSegment({x, y, z});
			}
		}
	}

	m_segments.loadGeneratedSegments();
}

void World::renderSector(MasterRenderer& renderer, const Frustum& frustum) {
	m_segments.render(renderer, frustum);
}

const std::tuple<int, int, int> World::getVoxelPos(int x, int y, int z) const {
	return std::tuple<int, int, int>(abs(x) % Segment::WIDTH, y, abs(z) % Segment::WIDTH);
}
