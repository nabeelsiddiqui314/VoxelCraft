#pragma once
#include "TypeRenderer.h"
#include <SFML/System/Clock.hpp>

class FloraRenderer : public TypeRenderer
{
public:
	FloraRenderer();
public:
	void render(const Camera& camera) override;
private:
	sf::Clock m_time;
};

