#pragma once
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
};

