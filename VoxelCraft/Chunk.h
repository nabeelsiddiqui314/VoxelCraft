#pragma once
#include "ChunkModels.h"

struct Chunk {
	ChunkBlocks chunk;
	ChunkModels models;
	bool hasMeshGenerated = false;
};