#include "stdafx.h"
#include "SolidRenderer.h"


SolidRenderer::SolidRenderer() {
	m_shader.loadShader("solid.vert", "solid.frag");
	m_texture.load("res/grass.png");
	m_texture.bind();
	m_shader.useProgram();
	m_shader.setUniform1i("u_texture", 0);
}

void SolidRenderer::addSolidChunk(const Model* solid) {
	m_solidChunks.emplace_back(solid);
}

void SolidRenderer::render(const Camera& camera) {
	m_shader.useProgram();
	glm::mat4 view = camera.getViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(70.0f), (float)1000 / (float)600, 0.1f, 1000.0f);
	m_shader.setUniformMat4("u_view", view);
	m_shader.setUniformMat4("u_projection", projection);

	glEnable(GL_CULL_FACE);
	for (std::int16_t i = 0; i < m_solidChunks.size(); i++) {
		m_solidChunks[i]->bindVao();
		glDrawElements(GL_TRIANGLES, m_solidChunks[i]->getRenderData().indicesCount, GL_UNSIGNED_INT, nullptr);
	}
}

SolidRenderer::~SolidRenderer()
{
}