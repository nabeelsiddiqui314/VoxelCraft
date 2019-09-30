#pragma once
#include "Model.h"
#include "Mesh.h"

struct SegmentModel
{
public:
	void cleanUp();
	void loadMeshToModel();
public:
	Model model;
	Mesh mesh;
};

struct MeshTypes {
	SegmentModel solid;
	SegmentModel water;
};