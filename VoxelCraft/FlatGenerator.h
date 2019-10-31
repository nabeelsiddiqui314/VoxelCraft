#pragma once
#include "MapGenerator.h"

class FlatGenerator : public MapGenerator
{
public:
	FlatGenerator(std::int16_t height);
public:
	virtual Sector generateSector(const VecXZ& pos) override;
private:
	const std::int16_t m_height;
};

