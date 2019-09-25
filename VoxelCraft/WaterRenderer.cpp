#include "stdafx.h"
#include "WaterRenderer.h"


WaterRenderer::WaterRenderer() : TypeRenderer("water") {}

void WaterRenderer::render(const Camera& camera) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	p_shader.useProgram();
	p_shader.setUniform1f("u_time", c.getElapsedTime().asMilliseconds() / 100);
	handleCameraTransform(camera);
	drawModels();
	glDisable(GL_BLEND);
}
