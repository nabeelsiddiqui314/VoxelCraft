#pragma once
#include "TypeRenderer.h"

class WaterRenderer : public TypeRenderer
{
public:
	WaterRenderer();
public:
	void render(const Camera& camera) override;
};

