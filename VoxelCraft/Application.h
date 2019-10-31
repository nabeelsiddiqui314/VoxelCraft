#pragma once
#include "MasterRenderer.h"
#include "VoxelCodex.h"
#include "StateManager.h"
#include "Game.h"
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
	StateManager m_stateManager;
	sf::Clock frameClock;
	int m_windowWidth;
	int m_windowHeight;
};

