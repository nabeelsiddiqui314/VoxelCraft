#pragma once
#include "BlockUpdateHandler.h"

class GroundFloraHandler : public BlockUpdateHandler
{
public:
	bool callUpdate(World& world, int x, int y, int z) override;
	int getCoolDownTime() const override;
};