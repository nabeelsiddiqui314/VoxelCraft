#pragma once
#include "MapGenerator.h"
#include <cstdint>

class FlatGenerator : public MapGenerator
{
public:
	FlatGenerator(std::int16_t height);
public:
	virtual void generateStack(SegmentStack& sector, int x, int z) override;
private:
	const std::int16_t m_height;
};

