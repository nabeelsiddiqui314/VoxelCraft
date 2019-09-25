#include "stdafx.h"
#include "WaterRenderer.h"


WaterRenderer::WaterRenderer() : TypeRenderer("water") {}

void WaterRenderer::render(const Camera& camera) {
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	handleCameraTransform(camera);
	drawModels();
}
