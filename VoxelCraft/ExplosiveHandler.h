#pragma once
#include "VoxelUpdateHandler.h"
#include <stdint.h>

namespace Voxel {
	class ExplosiveHandler : public UpdateHandler
	{
	public:
		ExplosiveHandler(int blocks);
	protected:
		bool callUpdate(World& world, int x, int y, int z) override;
		int getCoolDownTime() const override;
	private:
		const int m_numBlocks;
	};
}