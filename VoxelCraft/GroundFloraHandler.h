#pragma once
#include "BlockUpdateHandler.h"

class GroundFloraHandler : public BlockUpdateHandler
{
public:
	bool update(World& world, int x, int y, int z) override;
};