#pragma once
#include "TypeRenderer.h"
#include <SFML/System/Clock.hpp>

class WaterRenderer : public TypeRenderer
{
public:
	WaterRenderer();
public:
	void render(const Camera& camera, float worldtTime) override;
private:
	sf::Clock c;
};

