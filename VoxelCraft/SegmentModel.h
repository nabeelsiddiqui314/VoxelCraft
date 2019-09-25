#pragma once
#include "Model.h"
#include "Mesh.h"

struct SegmentModel
{
public:
	void loadMeshToModel();
public:
	Model model;
	Mesh mesh;
};

struct MeshTypes {
	SegmentModel solid;
};