#include "stdafx.h"
#include "MasterRenderer.h"

MasterRenderer::MasterRenderer() {
	m_shader.loadShader("shader.vert", "shader.frag");
	m_tex.load("res/grass.png");
	m_tex.bind();
	m_shader.useProgram();
	m_shader.setUniform1i("u_texture", 0);
}

void MasterRenderer::addChunk(const Model& model) {
	m_chunks.push_back(model);
}

void MasterRenderer::render(GLFWwindow* window, const Camera& camera) {
	glClearColor(0, 0.2, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader.useProgram();
	glm::mat4 view = camera.getViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(70.0f), (float)1000 / (float)600, 0.1f, 100.0f);
	m_shader.setUniformMat4("u_view", view);
	m_shader.setUniformMat4("u_projection", projection);

	glEnable(GL_CULL_FACE);
	m_chunks[0].bindVao();
	glDrawElements(GL_TRIANGLES, m_chunks[0].getRenderData().indicesCount, GL_UNSIGNED_INT, nullptr);
}