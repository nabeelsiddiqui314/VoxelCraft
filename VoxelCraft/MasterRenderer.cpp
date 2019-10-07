#include "stdafx.h"
#include "MasterRenderer.h"

MasterRenderer::MasterRenderer() {
	m_solidRenderer = std::make_unique<SolidRenderer>();
	m_waterRenderer = std::make_unique<WaterRenderer>();
}

void MasterRenderer::addChunk(const MeshTypes& models) {
	if (models.solid.model.getRenderData().VAO != 0)
		m_solidRenderer->addModel(&models.solid.model);

	if (models.water.model.getRenderData().VAO != 0)
		m_waterRenderer->addModel(&models.water.model);
}

void MasterRenderer::renderChunks(const Camera& camera) {
	glClearColor(0.59f, 0.74f, 0.87f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_solidRenderer->render(camera);
	m_waterRenderer->render(camera);
}