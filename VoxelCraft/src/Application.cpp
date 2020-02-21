#include "Application.h"
#include "OGl/Util/TextureAtlas.h"

Application::Application() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(1000, 600, "VoxelCraft", NULL, NULL);
	glfwMakeContextCurrent(m_window);
	if(glewInit() != GLEW_OK)
		return;

	glEnable(GL_DEPTH_TEST);
	m_renderer = std::make_unique<MasterRenderer>();

	TextureAtlas::init(8);

	m_stateManager.pushState(std::make_shared<Game>());

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Application::run() {
	while (!glfwWindowShouldClose(m_window)) {
		glfwGetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
		glViewport(0, 0, m_windowWidth, m_windowHeight);
		
		//glfwSetCursorPos(m_window, m_windowWidth / 2, m_windowHeight / 2);
		m_stateManager.getCurrentState()->update(frameClock.getElapsedTime().asSeconds());
		frameClock.restart();

		m_stateManager.getCurrentState()->render(*m_renderer);

		glfwSwapBuffers(m_window);
		glfwPollEvents();
		glfwSetWindowShouldClose(m_window, sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
	}
}

Application::~Application() {
	glfwTerminate();
}
