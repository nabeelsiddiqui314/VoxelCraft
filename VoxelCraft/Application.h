#pragma once
#include "MasterRenderer.h"

class Application
{
public:
	Application();
	~Application();
public:
	void run();
private:
	GLFWwindow* m_window;
	MasterRenderer m_renderer;
};

