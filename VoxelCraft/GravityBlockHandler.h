#pragma once
#include "BlockUpdateHandler.h"

class GravityBlockHandler : public BlockUpdateHandler
{
protected:
	bool callUpdate(World& world, int x, int y, int z) override;
	int getCoolDownTime() const override;
};

