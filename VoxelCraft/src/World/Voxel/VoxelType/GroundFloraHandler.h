#pragma once
#include "VoxelUpdateHandler.h"

namespace Voxel {
	class GroundFloraHandler : public UpdateHandler
	{
	public:
		bool callUpdate(World& world, int x, int y, int z) override;
		int getCoolDownTime() const override;
	};
}