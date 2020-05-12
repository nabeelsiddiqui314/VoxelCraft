#include "Segment.h"
#include "SegmentMeshGenerator.h"
#include "../../Renderer/MasterRenderer.h"
#include "../../Math/VecXZ.h"

Segment::Segment() 
	: m_opaqueCount(0),
	  m_voidCount(WIDTH * WIDTH * WIDTH) {}

void Segment::setNaturalLight(int x, int y, int z, int luminocity) {
	m_voxels[x + WIDTH * (y + WIDTH * z)].setNaturalLight(luminocity);
}

void Segment::setVoxel(int x, int y, int z, Voxel::Type id) {
	if (!isInBounds(x, y, z)) {
		return;
	}

	Voxel::Element ID = id;

	if (!getVoxel(x, y, z).getInfo().opaque && ID.getInfo().opaque)
		m_opaqueCount++;
	else if (getVoxel(x, y, z).getInfo().opaque && !ID.getInfo().opaque)
		m_opaqueCount--;

	if (getVoxel(x, y, z) != Voxel::Type::VOID && ID == Voxel::Type::VOID)
		m_voidCount++;
	else if (getVoxel(x, y, z) == Voxel::Type::VOID && ID != Voxel::Type::VOID)
		m_voidCount--;

	m_voxels[x + WIDTH * (y + WIDTH * z)] = id;

	if (ID.getType() == Voxel::Type::VOID && getVoxel(x, y, z).getNaturalLight() > 0) {
		m_lightcomputer.removeLight(x, y, z, this, getVoxel(x, y, z).getNaturalLight());
	}
	else if (ID.getInfo().luminocity > 0) {
		m_lightcomputer.addLight(x, y, z, this);
	}
}

Voxel::Element Segment::getVoxel(int x, int y, int z) const {
	if (!isInBounds(x, y, z)) {
		return Voxel::Type::VOID;
	}

	return m_voxels[x + WIDTH * (y + WIDTH * z)];
}

Voxel::Element Segment::getVoxelFromNeighborhood(int x, int y, int z) const {
	NeighborPosition neighborPos;
	bool isVoxelFromNeighbor = false;

	auto checkAxis = [&](int& axis, const NeighborPosition& lowerBound, const NeighborPosition& upperBound) {
		if (axis < 0) {
			axis += Segment::WIDTH;
			neighborPos = lowerBound;
			isVoxelFromNeighbor = true;
		}
		else if (axis > Segment::WIDTH - 1) {
			axis -= Segment::WIDTH;
			neighborPos = upperBound;
			isVoxelFromNeighbor = true;
		}
	};

	checkAxis(x, NeighborPosition::LEFT, NeighborPosition::RIGHT);
	checkAxis(y, NeighborPosition::BOTTTOM, NeighborPosition::TOP);
	checkAxis(z, NeighborPosition::BACK, NeighborPosition::FRONT);

	if (!isVoxelFromNeighbor) {
		return getVoxel(x, y, z);
	}

	auto neighborSegment = getNeighbor(neighborPos);
	if (neighborSegment) {
		return neighborSegment->getVoxel(x, y, z);
	}
	return Voxel::Type::VOID;
}

void Segment::setNeighbor(std::shared_ptr<Segment> neighbor, const NeighborPosition& pos) {
	m_neighbors[static_cast<std::size_t>(pos)] = neighbor;
}

std::shared_ptr<Segment> Segment::getNeighbor(const NeighborPosition& pos) const {
	return m_neighbors[static_cast<std::size_t>(pos)].lock();
}

bool Segment::isAllOpaque() const {
	return m_opaqueCount == WIDTH * WIDTH * WIDTH;
}

bool Segment::isEmpty() const {
	return m_voidCount == WIDTH * WIDTH * WIDTH;
}

bool Segment::isInBounds(int x, int y, int z) const {
	auto isOrdinateInBounds = [&](int o) {
		return o >= 0 && o < WIDTH;
	};

	return isOrdinateInBounds(x) && isOrdinateInBounds(y) && isOrdinateInBounds(z);
}