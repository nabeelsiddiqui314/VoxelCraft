#pragma once
#include "MasterRenderer.h"
#include "World.h"
#include <SFML/Graphics.hpp>

class Application
{
public:
	Application();
	~Application();
public:
	void run();
private:
	GLFWwindow* m_window;
	std::unique_ptr<MasterRenderer> m_renderer;
	std::unique_ptr<World> m_world;
	std::unique_ptr<Camera> cam;
	sf::Clock c, clock;
	float xLast, yLast;
};

