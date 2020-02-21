#pragma once
#include "TypeRenderer.h"

class SolidRenderer : public TypeRenderer
{
public:
	SolidRenderer();
public:
	void render(const Camera& camera, float worldtTime) override;
};

