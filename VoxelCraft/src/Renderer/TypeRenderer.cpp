#include "TypeRenderer.h"


TypeRenderer::TypeRenderer(const std::string& vert, const std::string& frag) {
	p_shader.loadShader(std::string("shaders/" + vert + ".vert").c_str(), std::string("shaders/" + frag + ".frag").c_str());
	p_shader.useProgram();
	p_shader.setUniform1i("u_texture", 0);
}

void TypeRenderer::addModel(const Model* model) {
	m_models.emplace_back(model);
}

void TypeRenderer::updateShader(const Camera& camera, float worldTime) {
	p_shader.setUniformMat4("u_view", camera.getViewMatrix());
	p_shader.setUniformMat4("u_projection", camera.getProjMatrix());
	p_shader.setUniform1f("u_density", 0.005f);
	p_shader.setUniform1f("u_gradient", 6.0f);

	p_shader.setUniform1f("u_worldTime", worldTime);
	p_shader.setUniform3f("u_skyColor", glm::vec3(0.59f, 0.74f, 0.87f) * worldTime);
	p_shader.setUniform1f("u_gamma", 1.0f/1.2f);
}

void TypeRenderer::drawModels() {
	for (auto& model : m_models) {
		model->bindVao();
		glDrawElements(GL_TRIANGLES, model->getRenderData().indicesCount, GL_UNSIGNED_INT, nullptr);
	}
	m_models.clear();
	m_models.shrink_to_fit();
}