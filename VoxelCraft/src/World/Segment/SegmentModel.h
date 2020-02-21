#pragma once
#include "../../OGL/Core/Mesh.h"
#include "../../OGL/Core/Model.h"

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
	SegmentModel liquid;
	SegmentModel flora;
};