#include "stdafx.h"
#include "MasterRenderer.h"

MasterRenderer::MasterRenderer() {
	m_solidRenderer = std::make_unique<SolidRenderer>();
	m_waterRenderer = std::make_unique<WaterRenderer>();
	m_floraRenderer = std::make_unique<FloraRenderer>();
}

void MasterRenderer::addSector(const MeshTypes& models) {
	if (models.solid.model.getRenderData().VAO != 0)
		m_solidRenderer->addModel(&models.solid.model);

	if (models.liquid.model.getRenderData().VAO != 0)
		m_waterRenderer->addModel(&models.liquid.model);

	if (models.flora.model.getRenderData().VAO != 0)
		m_floraRenderer->addModel(&models.flora.model);
}

void MasterRenderer::renderSector(const Camera& camera) {
	float time = std::max(0.5f + sin((float)m_worldClock.getElapsedTime().asSeconds() / 5.0f) / 2.0f, 0.02f);

	auto skyColor = glm::vec3(0.59f, 0.74f, 0.87f) * time;

	glClearColor(skyColor.x, skyColor.y, skyColor.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_solidRenderer->render(camera, time);
	m_waterRenderer->render(camera, time);
	m_floraRenderer->render(camera, time);
}