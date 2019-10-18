#pragma once
#include "NonCopyable.h"

class World;

class BlockUpdateHandler : public NonCopyable
{
public:
	BlockUpdateHandler() = default;
	virtual ~BlockUpdateHandler() {}
public:
	virtual bool update(World& world, int x, int y, int z);
};