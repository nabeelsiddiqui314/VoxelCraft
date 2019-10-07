#include "stdafx.h"
#include "FloraRenderer.h"


FloraRenderer::FloraRenderer() : TypeRenderer("flora") {}

void FloraRenderer::render(const Camera& camera) {
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	p_shader.useProgram();
	handleCameraTransform(camera);
	drawModels();
}