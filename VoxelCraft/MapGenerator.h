#pragma once
#include "Chunks.h"
#include "vecXZ.h"

class MapGenerator
{
public:
	virtual ~MapGenerator() {}
public:
	virtual Chunks generateChunk(const VecXZ& pos) = 0;
};

