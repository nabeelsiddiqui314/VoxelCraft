#pragma once
#include "../../OGL/Core/Model.h"
#include "SegmentMesh.h"


struct SegmentMeshes {
	SegmentMesh solid;
	SegmentMesh liquid;
	SegmentMesh flora;
};

struct SegmentModels {
	Model solid;
	Model liquid;
	Model flora;
};