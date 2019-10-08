#pragma once
#include "TypeRenderer.h"

class FloraRenderer : public TypeRenderer
{
public:
	FloraRenderer();
public:
	void render(const Camera& camera) override;
private:
	sf::Clock m_time;
};

