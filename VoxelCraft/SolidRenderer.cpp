#include "stdafx.h"
#include "SolidRenderer.h"


SolidRenderer::SolidRenderer() : TypeRenderer("solid") {}

void SolidRenderer::render(const Camera& camera) {
	glEnable(GL_CULL_FACE);
	p_shader.useProgram();
	handleCameraTransform(camera);
	drawModels();
}