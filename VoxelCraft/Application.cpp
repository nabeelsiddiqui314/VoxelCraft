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
	m_camera = std::make_unique<Camera>();
	BlockCodex::init();
	TextureAtlas::init(8);
}

void Application::run() {
	while (!glfwWindowShouldClose(m_window)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			m_camera->updateMovement(Camera::FORWARD, frameClock.getElapsedTime().asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			m_camera->updateMovement(Camera::LEFT, frameClock.getElapsedTime().asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			m_camera->updateMovement(Camera::BACKWARD, frameClock.getElapsedTime().asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			m_camera->updateMovement(Camera::RIGHT, frameClock.getElapsedTime().asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			m_camera->updateMovement(Camera::DOWN, frameClock.getElapsedTime().asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			m_camera->updateMovement(Camera::UP, frameClock.getElapsedTime().asSeconds());
		}
		frameClock.restart();

		m_camera->updateRotation(sf::Mouse::getPosition().x - xLast, -sf::Mouse::getPosition().y + yLast);
		xLast = sf::Mouse::getPosition().x;
		yLast = sf::Mouse::getPosition().y;

		m_world->update(*m_camera);
		m_world->renderChunks(*m_renderer, m_camera->getFrustum());
		m_renderer->render(m_window, *m_camera);
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

Application::~Application() {
	glfwTerminate();
}
