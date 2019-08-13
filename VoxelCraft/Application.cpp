#include "stdafx.h"
#include "Application.h"

Application::Application() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(1000, 600, "VoxelCraft", NULL, NULL);
	glfwMakeContextCurrent(m_window);
	if(glewInit() != GLEW_OK)
		return;

	glViewport(0, 0, 1000, 600);
	glEnable(GL_DEPTH_TEST);
	m_renderer = std::make_unique<MasterRenderer>();
	m_world = std::make_unique<World>();
	cam = std::make_unique<Camera>();
	m_renderer->addChunk(m_world->get());
}

void Application::run() {
	while (!glfwWindowShouldClose(m_window)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			cam->updateMovement(Camera::FORWARD, c.getElapsedTime().asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			cam->updateMovement(Camera::LEFT, c.getElapsedTime().asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			cam->updateMovement(Camera::BACKWARD, c.getElapsedTime().asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			cam->updateMovement(Camera::RIGHT, c.getElapsedTime().asSeconds());
		}

		cam->updateRotation(sf::Mouse::getPosition().x - xLast, -sf::Mouse::getPosition().y + yLast);
		xLast = sf::Mouse::getPosition().x;
		yLast = sf::Mouse::getPosition().y;

		m_renderer->render(m_window, *cam);
		glfwSwapBuffers(m_window);
		glfwPollEvents();
		c.restart();
	}
}

Application::~Application() {
	glfwTerminate();
}
