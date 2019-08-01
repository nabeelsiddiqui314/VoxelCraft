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
		0, 1, 2,
		2, 1, 3
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
		glClear(GL_COLOR_BUFFER_BIT);

		shader.useProgram();
		model.bindVao();
		glDrawElements(GL_TRIANGLES, model.getRenderData().indicesCount, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

Application::~Application() {
	glfwTerminate();
}
