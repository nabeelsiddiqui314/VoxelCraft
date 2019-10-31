#include "stdafx.h"
#include "VoxelUpdateHandler.h"

namespace Voxel {
	bool UpdateHandler::update(World& world, int x, int y, int z) {
		if (m_coolDownTimer.getElapsedTime().asMilliseconds() >= getCoolDownTime()) {
			m_coolDownTimer.restart();
			return callUpdate(world, x, y, z);
		}
		return false; // dont remove from list if it is in the midst of cool down
	}

	bool UpdateHandler::isUpdatable() const {
		return true;
	}
}