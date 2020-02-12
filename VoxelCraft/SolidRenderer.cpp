#include "stdafx.h"
#include "SolidRenderer.h"


SolidRenderer::SolidRenderer() : TypeRenderer("solid", "voxel") {}

void SolidRenderer::render(const Camera& camera) {
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	p_shader.useProgram();
	handleCameraTransform(camera);

	drawModels();
}