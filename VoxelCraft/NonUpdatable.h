#pragma once
#include "BlockUpdateHandler.h"

class NonUpdatable : public BlockUpdateHandler
{
public:
	bool isUpdatable() const override;
protected:
	virtual bool callUpdate(World& world, int x, int y, int z) override;
	virtual int getCoolDownTime() const override;
};

