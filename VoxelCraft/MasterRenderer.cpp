#include "stdafx.h"
#include "MasterRenderer.h"

MasterRenderer::MasterRenderer() {
}

void MasterRenderer::addChunk(const ChunkModels& models) {
	if (models.solid.model.has_value())
		m_solidRenderer.addSolidChunk(&models.solid.model.value());
}

void MasterRenderer::render(GLFWwindow* window, const Camera& camera) {
	glClearColor(0, 0.2, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_solidRenderer.render(camera);
}