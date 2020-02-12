#include "stdafx.h"
#include "WaterRenderer.h"


WaterRenderer::WaterRenderer() : TypeRenderer("water", "voxel") {
	p_shader.setUniform1f("u_amplitude", 0.5);
	p_shader.setUniform1f("u_frequency", 0.05);
}

void WaterRenderer::render(const Camera& camera, float worldtTime) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);

	p_shader.useProgram();
	p_shader.setUniform1f("u_time", c.getElapsedTime().asMilliseconds() / 100);
	updateShader(camera, worldtTime);

	drawModels();
}
