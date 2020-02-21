#include "GravityHandler.h"
#include "../../World.h"
#include "../../Voxel/VoxelCodex.h"

namespace Voxel {
	bool GravityHandler::callUpdate(World& world, int x, int y, int z) {
		auto voxel = world.getVoxel(x, y, z);

		if (world.getVoxel(x, y - 1, z) == Type::VOID ||
			world.getVoxel(x, y - 1, z).getInfo().shaderType == ShaderType::LIQUID) {
			world.setVoxel(x, y, z, Type::VOID);
			world.setVoxel(x, y - 1, z, voxel.getType());
		}

		return true;
	}

	int GravityHandler::getCoolDownTime() const {
		return 10;
	}
}