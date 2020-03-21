#include "LightingComputer.h"
#include "Segment.h"

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

			if (!segment->getVoxel(X, Y, Z).getInfo().opaque &&
				segment->getVoxel(X, Y, Z).getNaturalLight() <= luminocity - 2) {

				addLight(X, Y, Z, segment);
				segment->setNaturalLight(X, Y, Z, luminocity - 1);
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

			int neighborLevel = segment->getVoxel(X, Y, Z).getNaturalLight();

			if (neighborLevel != 0 && neighborLevel < lightLevel) {
				removeLight(X, Y, Z, segment, neighborLevel);
			}
			else if (neighborLevel >= lightLevel) {
				Vector3 pos = { X, Y, Z };
				m_lightQueue.emplace(pos, segment);
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