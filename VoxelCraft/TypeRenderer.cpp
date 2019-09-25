#include "stdafx.h"
#include "TypeRenderer.h"


TypeRenderer::TypeRenderer(const std::string& shader) {
	m_shader.loadShader(std::string(shader + ".vert").c_str(), std::string(shader + ".frag").c_str());
	m_shader.useProgram();
	m_shader.setUniform1i("u_texture", 0);
}

void TypeRenderer::addModel(const Model* model) {
	m_models.emplace_back(model);
}

void TypeRenderer::handleCameraTransform(const Camera& camera) {
	m_shader.useProgram();
	glm::mat4 view = camera.getViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(70.0f), (float)1000 / (float)600, 0.1f, 1000.0f);
	m_shader.setUniformMat4("u_view", view);
	m_shader.setUniformMat4("u_projection", projection);
}

void TypeRenderer::drawModels() {
	for (auto& model : m_models) {
		model->bindVao();
		glDrawElements(GL_TRIANGLES, model->getRenderData().indicesCount, GL_UNSIGNED_INT, nullptr);
	}
	m_models.clear();
	m_models.shrink_to_fit();
}
