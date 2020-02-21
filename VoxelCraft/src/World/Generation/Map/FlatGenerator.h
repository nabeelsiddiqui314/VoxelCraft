#pragma once
#include "MapGenerator.h"
#include <cstdint>

class FlatGenerator : public MapGenerator
{
public:
	FlatGenerator(std::int16_t height);
public:
	virtual void generateSector(Sector& sector, const VecXZ& pos) override;
private:
	const std::int16_t m_height;
};

