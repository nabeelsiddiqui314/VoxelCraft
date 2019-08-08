#pragma once
#include "MapGenerator.h"

class FlatGenerator : public MapGenerator
{
public:
	virtual Chunk generateChunk(const VecXZ& pos) override;
};

