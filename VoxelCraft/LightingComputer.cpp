#include "stdafx.h"
#include "LightingComputer.h"
#include "Segment.h"
#include "SegmentBounds.h"

void LightingComputer::addLight(int x, int y, int z, int luminocity, Segment* segment) {
	segment->setNaturalLight(x, y, z, luminocity);
	segment->regenMesh();
	Vector3 pos = {x, y, z};
	m_lightQueue.emplace(pos, segment);
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
				addLight(X, Y, Z, luminocity - 1, SegmentBounds::getInstance().getSegment(*segment, X, Y, Z));
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