#include "stdafx.h"
#include "SegmentModel.h"

void SegmentModel::cleanUp() {
	mesh.vertices.clear();
	mesh.indices.clear();
	mesh.textureCoords.clear();
	mesh.naturalLight.clear();
	mesh.skyExposure.clear();

	mesh.vertices.shrink_to_fit();
	mesh.indices.shrink_to_fit();
	mesh.textureCoords.shrink_to_fit();
	mesh.naturalLight.shrink_to_fit();
	mesh.skyExposure.clear();
}

void SegmentModel::loadMeshToModel() {
	if (!mesh.vertices.empty()) {
		model.addMesh(mesh);
		cleanUp();
	}
}
