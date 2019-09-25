#include "stdafx.h"
#include "WaterRenderer.h"


WaterRenderer::WaterRenderer() : TypeRenderer("water") {}

void WaterRenderer::render(const Camera& camera) {
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	p_shader.useProgram();
	p_shader.setUniform1f("u_time", c.getElapsedTime().asSeconds());
	handleCameraTransform(camera);
	drawModels();
}
