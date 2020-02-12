#pragma once
#include <memory>
#include "TypeRenderer.h"
#include "WaterRenderer.h"
#include "SolidRenderer.h"
#include "FloraRenderer.h"
#include "SegmentModel.h"
#include <GLFW/glfw3.h>

class MasterRenderer
{
public:
	MasterRenderer();
public:
	void addSector(const MeshTypes& models);
	void renderSector(const Camera& camera);
private:
	std::unique_ptr<TypeRenderer> m_solidRenderer;
	std::unique_ptr<TypeRenderer> m_waterRenderer;
	std::unique_ptr<TypeRenderer> m_floraRenderer;
	sf::Clock m_worldClock;
};

