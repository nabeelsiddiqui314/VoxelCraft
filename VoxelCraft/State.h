#pragma once
#include <memory>
#include "MasterRenderer.h"
#include "NonCopyable.h"

class State : public NonCopyable
{
public:
	virtual ~State() {}
public:
	virtual void update(float dt) = 0;
	virtual void render(MasterRenderer& renderer) = 0;
};

