#pragma once
#include "BlockUpdateHandler.h"

class LiquidHandler : public BlockUpdateHandler
{
public:
	bool callUpdate(World& world, int x, int y, int z) override;
	int getCoolDownTime() const override;
};

