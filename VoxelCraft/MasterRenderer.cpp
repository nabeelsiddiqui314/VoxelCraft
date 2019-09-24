#include "stdafx.h"
#include "MasterRenderer.h"

MasterRenderer::MasterRenderer() {
}

void MasterRenderer::addChunk(const Model& models) {
	//if (models.solid.model.has_value())
	m_solidRenderer.addSolidChunk(&models);
}

void MasterRenderer::render(GLFWwindow* window, const Camera& camera) {
	glClearColor(0, 0.2, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_solidRenderer.render(camera);
}