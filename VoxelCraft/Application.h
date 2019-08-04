#pragma once
#include "Shader.h"
#include "Model.h"
#include "Texture.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
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
	Shader shader;
	Model model;
	Texture tex;
	Camera cam;
	float xLast, yLast;
	sf::Clock c;
	sf::Clock clock;
	Camera::Direction dir;
};

