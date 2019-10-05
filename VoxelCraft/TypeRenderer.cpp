#include "stdafx.h"
#include "TypeRenderer.h"


TypeRenderer::TypeRenderer(const std::string& shader) {
	p_shader.loadShader(std::string("shaders/" + shader + ".vert").c_str(), std::string("shaders/" + shader + ".frag").c_str());
	p_shader.useProgram();
	p_shader.setUniform1i("u_texture", 0);
}

void TypeRenderer::addModel(const Model* model) {
	m_models.emplace_back(model);
}

void TypeRenderer::handleCameraTransform(const Camera& camera) {
	p_shader.useProgram();
	p_shader.setUniformMat4("u_view", camera.getViewMatrix());
	p_shader.setUniformMat4("u_projection", camera.getProjMatrix());
}

void TypeRenderer::drawModels() {
	for (auto& model : m_models) {
		model->bindVao();
		glDrawElements(GL_TRIANGLES, model->getRenderData().indicesCount, GL_UNSIGNED_INT, nullptr);
	}
	m_models.clear();
	m_models.shrink_to_fit();
}
