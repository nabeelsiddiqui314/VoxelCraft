#pragma once
#include "VoxelUpdateHandler.h"

namespace Voxel {
	class NonUpdatable : public UpdateHandler
	{
	public:
		bool isUpdatable() const override;
	protected:
		virtual bool callUpdate(World& world, int x, int y, int z) override;
		virtual int getCoolDownTime() const override;
	};
}