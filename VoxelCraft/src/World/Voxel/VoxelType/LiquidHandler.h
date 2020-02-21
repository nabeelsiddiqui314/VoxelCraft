#pragma once
#include "VoxelUpdateHandler.h"

namespace Voxel {
	class LiquidHandler : public UpdateHandler
	{
	public:
		bool callUpdate(World& world, int x, int y, int z) override;
		int getCoolDownTime() const override;
	};
}