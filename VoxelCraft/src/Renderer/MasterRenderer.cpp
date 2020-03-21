#include "MasterRenderer.h"
#include "../World/Segment/SegmentModels.h"
#include "TypeRenderer.h"
#include "SolidRenderer.h"
#include "WaterRenderer.h"
#include "FloraRenderer.h"


MasterRenderer::MasterRenderer() {
	m_solidRenderer = std::make_unique<SolidRenderer>();
	m_waterRenderer = std::make_unique<WaterRenderer>();
	m_floraRenderer = std::make_unique<FloraRenderer>();
}

void MasterRenderer::addSegment(const SegmentModels& models) {
	if (models.solid.getRenderData().VAO != 0)
		m_solidRenderer->addModel(&models.solid);

	if (models.liquid.getRenderData().VAO != 0)
		m_waterRenderer->addModel(&models.liquid);

	if (models.flora.getRenderData().VAO != 0)
		m_floraRenderer->addModel(&models.flora);
}

void MasterRenderer::renderSegments(const Camera& camera) {
	float time = std::max(0.5f + sin((float)m_worldClock.getElapsedTime().asSeconds() / 5.0f) / 2.0f, 0.02f);

	auto skyColor = glm::vec3(0.59f, 0.74f, 0.87f) * time;

	glClearColor(skyColor.x, skyColor.y, skyColor.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_solidRenderer->render(camera, time);
	m_waterRenderer->render(camera, time);
	m_floraRenderer->render(camera, time);
}