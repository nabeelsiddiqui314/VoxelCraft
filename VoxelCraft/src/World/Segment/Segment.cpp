#include "Segment.h"
#include "SegmentStack.h"
#include "../../Renderer/MasterRenderer.h"

Segment::Segment(int x, int y, int z)
	: m_opaqueCount(0),
	  m_voidCount(WIDTH * WIDTH * WIDTH),
      m_worldPosition(x, y, z) {
	m_neighbors.fill(nullptr);
}

void Segment::setNaturalLight(int x, int y, int z, int luminocity) {
	if (!isInBounds(x, y, z)) {
		auto neighborPos = getNeighborPosition(x, y, z);
		if (neighborPos.parent) {
			neighborPos.parent->setNaturalLight(neighborPos.x, neighborPos.y, neighborPos.z, luminocity);
		}
	}

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
		auto neighborPos = getNeighborPosition(x, y, z);
		if (neighborPos.parent) {
			return neighborPos.parent->getVoxel(neighborPos.x, neighborPos.y, neighborPos.z);
		}
		return Voxel::Type::VOID;
	}

	return m_voxels[x + WIDTH * (y + WIDTH * z)];
}

const Vector3& Segment::getWorldPosition() const {
	return m_worldPosition;
}

void Segment::setNeighborSegment(const Neighbor& neighborPos, Segment* segment) {
	m_neighbors[neighbor(neighborPos)] = segment;
}

const Segment* Segment::getNeighborSegment(const Neighbor& neighborPos) const {
	return m_neighbors[neighbor(neighborPos)];
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

std::uint8_t Segment::neighbor(const Neighbor& neighbor) const {
	return static_cast<std::uint8_t>(neighbor);
}

Segment::NeighborPosition Segment::getNeighborPosition(int x, int y, int z) const {
	if (x < 0) {
		if (m_neighbors[neighbor(Neighbor::LEFT)]) {
			x += Segment::WIDTH;
			return { x, y, z, m_neighbors[neighbor(Neighbor::LEFT)] };
		}
	}
	else if (x >= Segment::WIDTH) {
		if (m_neighbors[neighbor(Neighbor::RIGHT)]) {
			x = x - Segment::WIDTH;
			return { x, y, z, m_neighbors[neighbor(Neighbor::RIGHT)] };
		}
	}

	if (y < 0) {
		if (m_neighbors[neighbor(Neighbor::BOTTOM)]) {
			y += Segment::WIDTH;
			return { x, y, z, m_neighbors[neighbor(Neighbor::BOTTOM)] };
		}
	}
	else if (y >= Segment::WIDTH) {
		if (m_neighbors[neighbor(Neighbor::TOP)]) {
			y = y - Segment::WIDTH;
			return { x, y, z, m_neighbors[neighbor(Neighbor::BOTTOM)] };
		}
	}

	if (z < 0) {
		if (m_neighbors[neighbor(Neighbor::BACK)]) {
			z += Segment::WIDTH;
			return { x, y, z, m_neighbors[neighbor(Neighbor::BACK)] };
		}
	}
	else if (z >= Segment::WIDTH) {
		if (m_neighbors[neighbor(Neighbor::FRONT)]) {
			z = z - Segment::WIDTH;
			return { x, y, z, m_neighbors[neighbor(Neighbor::FRONT)] };
		}
	}
}
