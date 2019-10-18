#include "stdafx.h"
#include "GroundFloraHandler.h"
#include "World.h"

bool GroundFloraHandler::update(World& world, int x, int y, int z) {
	if (world.getBlock(x, y - 1, z) == BlockType::VOID || world.getBlock(x, y - 1, z) == BlockType::WATER) {
		world.setBlock(x, y, z, BlockType::VOID);
	}
	return true;
}