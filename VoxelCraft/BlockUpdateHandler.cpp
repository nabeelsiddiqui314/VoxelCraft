#include "stdafx.h"
#include "BlockUpdateHandler.h"


bool BlockUpdateHandler::update(World& world, int x, int y, int z) {
	if (m_coolDownTimer.getElapsedTime().asMilliseconds() >= getCoolDownTime()) {
		m_coolDownTimer.restart();
		return callUpdate(world, x, y, z);
	}
	return false; // dont remove from list if it is in the midst of cool down
}

bool BlockUpdateHandler::isUpdatable() const {
	return true;
}