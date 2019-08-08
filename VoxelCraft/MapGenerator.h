#pragma once
#include "Chunk.h"

class MapGenerator
{
public:
	MapGenerator();
	virtual ~MapGenerator() {}
public:
	virtual Chunk& generateChunk(std::int16_t x, std::int16_t y) = 0;
};

