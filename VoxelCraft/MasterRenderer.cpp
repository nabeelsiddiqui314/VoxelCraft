#include "stdafx.h"
#include "MasterRenderer.h"

MasterRenderer::MasterRenderer() {
}

void MasterRenderer::addChunk(const MeshTypes& models) {
	if (models.solid.model.getRenderData().VAO != 0)
		m_solidRenderer.addSolidChunk(&models.solid.model);
}

void MasterRenderer::render(GLFWwindow* window, const Camera& camera) {
	glClearColor(0, 0.2, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_solidRenderer.render(camera);
}