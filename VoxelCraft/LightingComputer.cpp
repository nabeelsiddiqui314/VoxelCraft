#include "stdafx.h"
#include "LightingComputer.h"
#include "Segment.h"
#include "SegmentBounds.h"

void LightingComputer::addLight(int x, int y, int z, Segment* segment) {
	Vector3 pos = {x, y, z};
	m_lightQueue.emplace(pos, segment);
	segment->setNaturalLight(x, y, z, segment->getVoxel(x, y, z).getInfo().luminocity);
}

void LightingComputer::removeLight(int x, int y, int z, Segment* segment, int lightLevel) {
	Vector3 pos = { x, y, z };
	m_lightRemovalQueue.emplace(pos, segment, lightLevel);
	segment->setNaturalLight(x, y, z, 0);
}

void LightingComputer::propogate() {
	propogateRemove();
	propogateAdd();
}

void LightingComputer::propogateAdd() {
	while (!m_lightQueue.empty()) {
		auto& lightNode = m_lightQueue.front();
		auto pos = lightNode.pos;
		auto segment = lightNode.parent;

		m_lightQueue.pop();

		int luminocity = segment->getVoxel(pos.x, pos.y, pos.z).getNaturalLight();

		auto spreadLight = [&](int X, int Y, int Z) {
			X += pos.x;
			Y += pos.y;
			Z += pos.z;

			if (!SegmentBounds::getInstance().getVoxel(*segment, X, Y, Z).getInfo().opaque &&
				SegmentBounds::getInstance().getVoxel(*segment, X, Y, Z).getNaturalLight() <= luminocity - 2) {

				int ox = adjustOrdinate(X);
				int oy = adjustOrdinate(Y);
				int oz = adjustOrdinate(Z);

				auto lightSegment = SegmentBounds::getInstance().getSegment(*segment, X, Y, Z);

				addLight(ox, oy, oz, lightSegment);
				lightSegment->setNaturalLight(ox, oy, oz, luminocity - 1);
				lightSegment->regenMesh();
			}
		};

		spreadLight( 0,  1,  0);
		spreadLight( 0, -1,  0);
		spreadLight(-1,  0,  0);
		spreadLight( 1,  0,  0);
		spreadLight( 0,  0,  1);
		spreadLight( 0,  0, -1);
	}
}

void LightingComputer::propogateRemove() {
	while (!m_lightRemovalQueue.empty()) {
		auto& removalNode = m_lightRemovalQueue.front();
		auto pos = removalNode.pos;
		auto segment = removalNode.parent;
		int lightLevel = removalNode.lvl;

		m_lightRemovalQueue.pop();

		auto spreadRemoval = [&](int X, int Y, int Z) {
			X += pos.x;
			Y += pos.y;
			Z += pos.z;

			int ox = adjustOrdinate(X);
			int oy = adjustOrdinate(Y);
			int oz = adjustOrdinate(Z);

			auto lightSegment = SegmentBounds::getInstance().getSegment(*segment, X, Y, Z);

			int neighborLevel = SegmentBounds::getInstance().getVoxel(*segment, X, Y, Z).getNaturalLight();

			if (neighborLevel != 0 && neighborLevel < lightLevel) {
				removeLight(ox, oy, oz, lightSegment, neighborLevel);
				lightSegment->regenMesh();
			}
			else if (neighborLevel >= lightLevel) {
				Vector3 pos = { ox, oy, oz };
				m_lightQueue.emplace(pos, lightSegment);
			}

		};

		spreadRemoval( 0,  1,  0);
		spreadRemoval( 0, -1,  0);
		spreadRemoval(-1,  0,  0);
		spreadRemoval( 1,  0,  0);
		spreadRemoval( 0,  0,  1);
		spreadRemoval( 0,  0, -1);
	}
}

int LightingComputer::adjustOrdinate(int ordinate) {
	if (ordinate < 0) {
		return Segment::WIDTH - abs(ordinate);
	}
	else if (ordinate >= Segment::WIDTH) {
		return ordinate % Segment::WIDTH;
	}
	return ordinate;
}