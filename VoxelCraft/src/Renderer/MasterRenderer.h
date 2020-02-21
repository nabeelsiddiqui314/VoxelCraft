#pragma once
#include <memory>
#include <GL/glew.h>
#include <SFML/System/Clock.hpp>
#include "TypeRenderer.h"

class Camera;
struct MeshTypes;

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

