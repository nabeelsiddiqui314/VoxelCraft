#include "stdafx.h"
#include "Application.h"

Application::Application() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(800, 600, "VoxelCraft", NULL, NULL);
	glfwMakeContextCurrent(m_window);
	if(glewInit() != GLEW_OK)
		return;

	glViewport(0, 0, 800, 600);

	shader.loadShader("shader.vert", "shader.frag");
	glEnable(GL_DEPTH_TEST);

	Mesh mesh;
	mesh.vertices = std::vector<GLfloat> {
		0, 0, 0,
		0, 1, 0,
		1, 0, 0,
		1, 1, 0
	};

	mesh.textureCoords = std::vector<GLfloat>{
		0, 0,
		0, 1,
		1, 0,
		1, 1,
	};

	mesh.indices = std::vector<GLuint> {
		0, 2, 3,
		3, 1, 0
	};
	model.addMesh(mesh);
	tex.load("res/grass.png");
	tex.bind();
	shader.useProgram();
	shader.setUniform1i("u_texture", 0);
}

void Application::run() {
	while (!glfwWindowShouldClose(m_window)) {
		glClearColor(0.2, 0.4, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {	
			cam.updateMovement(Camera::FORWARD, c.getElapsedTime().asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			cam.updateMovement(Camera::LEFT, c.getElapsedTime().asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			cam.updateMovement(Camera::BACKWARD, c.getElapsedTime().asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			cam.updateMovement(Camera::RIGHT, c.getElapsedTime().asSeconds());
		}

		if (clock.getElapsedTime().asSeconds() > 1 / 60.0f) {
			cam.updateRotation(sf::Mouse::getPosition().x - xLast, -sf::Mouse::getPosition().y + yLast);
			xLast = sf::Mouse::getPosition().x;
			yLast = sf::Mouse::getPosition().y;
			clock.restart();
		}
		shader.useProgram();
		glm::mat4 view = cam.getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(70.0f), (float)800 / (float)600, 0.1f, 100.0f);

		shader.setUniformMat4("u_view", view);
		shader.setUniformMat4("u_projection", projection);

		glEnable(GL_CULL_FACE);
		model.bindVao();
		glDrawElements(GL_TRIANGLES, model.getRenderData().indicesCount, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(m_window);
		glfwPollEvents();
		c.restart();
	}
}

Application::~Application() {
	glfwTerminate();
}
