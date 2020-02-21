#pragma once
#include "Renderer/MasterRenderer.h"
#include "World/Voxel/VoxelCodex.h"
#include "State/StateManager.h"
#include "State/Game.h"
#include <SFML/Window/Keyboard.hpp>
#include <GLFW/glfw3.h>

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

