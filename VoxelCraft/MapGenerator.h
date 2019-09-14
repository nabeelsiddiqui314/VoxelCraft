#pragma once
#include "ChunkBlocks.h"
#include "vecXZ.h"

class MapGenerator
{
public:
	virtual ~MapGenerator() {}
public:
	virtual ChunkBlocks generateChunk(const VecXZ& pos) = 0;
};

