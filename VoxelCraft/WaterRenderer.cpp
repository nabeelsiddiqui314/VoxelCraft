#include "stdafx.h"
#include "WaterRenderer.h"


WaterRenderer::WaterRenderer() : TypeRenderer("water") {
	p_shader.setUniform1f("u_amplitude", 0.5);
	p_shader.setUniform1f("u_frequency", 0.05);
	p_shader.setUniform4f("u_alphaMultiplier", {1.0f, 1.0f, 1.0f, 0.5f});
}

void WaterRenderer::render(const Camera& camera) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	p_shader.useProgram();
	p_shader.setUniform1f("u_time", c.getElapsedTime().asMilliseconds() / 100);
	handleCameraTransform(camera);
	drawModels();
}
