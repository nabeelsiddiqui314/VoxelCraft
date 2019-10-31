#include "stdafx.h"
#include "GroundFloraHandler.h"
#include "World.h"
	
namespace Voxel {
	bool GroundFloraHandler::callUpdate(World& world, int x, int y, int z) {
		if (world.getVoxel(x, y - 1, z) == Voxel::Type::VOID || world.getVoxel(x, y - 1, z) == Voxel::Type::WATER) {
			world.setVoxel(x, y, z, Voxel::Type::VOID);
		}
		return true;
	}

	int GroundFloraHandler::getCoolDownTime() const {
		return 0;
	}
}