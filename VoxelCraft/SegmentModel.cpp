#include "stdafx.h"
#include "SegmentModel.h"

void SegmentModel::loadMeshToModel() {
	if (!mesh.vertices.empty()) {
		model.addMesh(mesh);

		mesh.vertices.clear();
		mesh.indices.clear();
		mesh.textureCoords.clear();
		mesh.lightFactorData.clear();

		mesh.vertices.shrink_to_fit();
		mesh.indices.shrink_to_fit();
		mesh.textureCoords.shrink_to_fit();
		mesh.lightFactorData.shrink_to_fit();
	}
}
