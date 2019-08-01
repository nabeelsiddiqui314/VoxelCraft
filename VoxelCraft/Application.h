#pragma once
#include "Shader.h"
#include "Model.h"
#include "Texture.h"
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
	Shader shader;
	Model model;
	Texture tex;
};

