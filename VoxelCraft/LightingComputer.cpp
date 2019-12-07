#include "stdafx.h"
#include "LightingComputer.h"
#include "Segment.h"
#include "SegmentBounds.h"

void LightingComputer::addLight(int x, int y, int z, Segment* segment) {
	Vector3 pos = {x, y, z};
	m_lightQueue.emplace(pos, segment);
	segment->setNaturalLight(x, y, z, segment->getVoxel(x, y, z).getInfo().luminocity);
}

void LightingComputer::propogate() {
	while (!m_lightQueue.empty()) {
		auto& lightVoxel = m_lightQueue.front();
		auto pos = lightVoxel.pos;
		auto segment = lightVoxel.parent;

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
				segment->regenMesh();
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

int LightingComputer::adjustOrdinate(int ordinate) {
	if (ordinate < 0) {
		return Segment::WIDTH - abs(ordinate);
	}
	else if (ordinate >= Segment::WIDTH) {
		return ordinate % Segment::WIDTH;
	}
	return ordinate;
}