#pragma once
#include "ChunkModelsMaker.h"

struct Chunk {
	ChunkBlocks chunk;
	ChunkModelsMaker models;
	bool hasMeshGenerated = false;
};