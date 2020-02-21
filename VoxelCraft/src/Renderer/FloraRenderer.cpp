#include "FloraRenderer.h"


FloraRenderer::FloraRenderer() : TypeRenderer("flora", "voxel") {
	p_shader.useProgram();
	p_shader.setUniform1f("u_amplitude", 0.1f);
	p_shader.setUniform1f("u_frequency", 0.5f);
}

void FloraRenderer::render(const Camera& camera, float worldtTime) {
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	p_shader.useProgram();
	p_shader.setUniform1f("u_time", m_time.getElapsedTime().asMilliseconds() / 100);
	updateShader(camera, worldtTime);

	drawModels();
}