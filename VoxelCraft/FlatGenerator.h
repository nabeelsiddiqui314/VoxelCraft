#pragma once
#include "MapGenerator.h"

class FlatGenerator : public MapGenerator
{
public:
	FlatGenerator(std::int16_t height);
public:
	virtual Chunks generateChunk(const VecXZ& pos) override;
private:
	const std::int16_t m_height;
};

