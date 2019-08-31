#pragma once
#include "MeshGenerator.h"

struct Chunk {
	ChunkBlocks chunk;
	MeshGenerator models;
	bool hasMeshGenerated = false;
};