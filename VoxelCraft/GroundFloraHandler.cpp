#include "stdafx.h"
#include "GroundFloraHandler.h"
#include "World.h"
	

bool GroundFloraHandler::callUpdate(World& world, int x, int y, int z) {
	if (world.getBlock(x, y - 1, z) == BlockType::VOID || world.getBlock(x, y - 1, z) == BlockType::WATER) {
		world.setBlock(x, y, z, BlockType::VOID);
	}
	return true;
}

int GroundFloraHandler::getCoolDownTime() const {
	return 0;
}