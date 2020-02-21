#include "SolidRenderer.h"

SolidRenderer::SolidRenderer() : TypeRenderer("solid", "voxel") {}

void SolidRenderer::render(const Camera& camera, float worldtTime) {
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	p_shader.useProgram();
	updateShader(camera, worldtTime);

	drawModels();
}