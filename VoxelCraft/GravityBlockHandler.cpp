#include "stdafx.h"
#include "GravityBlockHandler.h"
#include "World.h"

bool GravityBlockHandler::callUpdate(World& world, int x, int y, int z) {
	auto block = world.getBlock(x, y, z);

	if (world.getBlock(x, y - 1, z) == BlockType::VOID ||
		BlockCodex::getBlockData(world.getBlock(x, y - 1, z)).shaderType == ShaderType::LIQUID) {
		world.setBlock(x, y, z, BlockType::VOID);
		world.setBlock(x, y - 1, z, block);
	}

	return true;
}

int GravityBlockHandler::getCoolDownTime() const {
	return 0;
}