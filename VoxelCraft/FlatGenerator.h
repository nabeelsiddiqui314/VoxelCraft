#pragma once
#include "MapGenerator.h"

class FlatGenerator : public MapGenerator
{
public:
	virtual ChunkBlocks generateChunk(const VecXZ& pos) override;
};

