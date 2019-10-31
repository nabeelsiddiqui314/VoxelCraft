#pragma once
#include "VoxelUpdateHandler.h"

namespace Voxel {
	class GravityHandler : public UpdateHandler
	{
	protected:
		bool callUpdate(World& world, int x, int y, int z) override;
		int getCoolDownTime() const override;
	};
}