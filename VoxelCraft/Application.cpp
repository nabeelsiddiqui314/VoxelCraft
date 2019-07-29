#include "stdafx.h"
#include "Application.h"


Application::Application() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(800, 600, "VoxelCraft", NULL, NULL);
	glfwMakeContextCurrent(m_window);
	glViewport(0, 0, 800, 600);
}

void Application::run() {
	while (!glfwWindowShouldClose(m_window)) {
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

Application::~Application() {
	glfwTerminate();
}
