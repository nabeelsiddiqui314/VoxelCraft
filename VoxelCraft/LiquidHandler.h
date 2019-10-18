#pragma once
#include "BlockUpdateHandler.h"

class LiquidHandler : public BlockUpdateHandler
{
public:
	bool update(World& world, int x, int y, int z) override;
};

