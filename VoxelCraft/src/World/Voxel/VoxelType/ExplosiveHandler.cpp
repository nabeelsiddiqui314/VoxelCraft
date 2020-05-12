#include "ExplosiveHandler.h"
#include "../../World.h"
#include <queue>
#include "../../../Math/vector3.h"

Voxel::ExplosiveHandler::ExplosiveHandler(int blocks)
 : m_numBlocks(blocks) {}

bool Voxel::ExplosiveHandler::callUpdate(World& world, int x, int y, int z) {
	std::queue<Vector3> destroyQueue;

	destroyQueue.emplace(x, y, z);
	int count = 0;

	while (!destroyQueue.empty()) {
		auto pos = destroyQueue.front();
		destroyQueue.pop();
		world.setVoxel(pos.x, pos.y, pos.z, Type::VOID);

		auto tryPropogate = [&](int x, int y, int z) {
			if (world.getVoxel(pos.x + x, pos.y + y, pos.z + z).getType() != Type::VOID) {
				destroyQueue.emplace(pos.x + x, pos.y + y, pos.z + z);
				count++;
			}
		};

		if (count < m_numBlocks) {
			tryPropogate( 1,  0,  0);
			tryPropogate(-1,  0,  0);
			tryPropogate( 0,  1,  0);
			tryPropogate( 0, -1,  0);
			tryPropogate( 0,  0,  1);
			tryPropogate( 0,  0, -1);
		}
	}
	return true;
}

int Voxel::ExplosiveHandler::getCoolDownTime() const {
	return 1000;
}