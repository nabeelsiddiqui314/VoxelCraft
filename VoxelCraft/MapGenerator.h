#pragma once
#include "Chunk.h"
#include "vecXZ.h"

class MapGenerator
{
public:
	MapGenerator();
	virtual ~MapGenerator() {}
public:
	virtual Chunk generateChunk(const VecXZ& pos) = 0;
};

