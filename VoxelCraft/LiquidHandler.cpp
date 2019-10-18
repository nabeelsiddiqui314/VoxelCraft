#include "stdafx.h"
#include "LiquidHandler.h"
#include "World.h"

bool LiquidHandler::callUpdate(World& world, int x, int y, int z) {
	auto block = world.getBlock(x, y, z);
	auto tryAdd = [&](int X, int Y, int Z) {
		if (world.getBlock(X, Y, Z) == BlockType::VOID) {
			world.setBlock(X, Y, Z, block);
		}
	};

	tryAdd(x + 1, y, z);
	tryAdd(x - 1, y, z);
	tryAdd(x, y, z + 1);
	tryAdd(x, y, z - 1);
	tryAdd(x, y - 1, z);

	return true;
}

int LiquidHandler::getCoolDownTime() const {
	return 10;
}
