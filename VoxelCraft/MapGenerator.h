#pragma once
#include "Sector.h"
#include "vecXZ.h"

class MapGenerator
{
public:
	virtual ~MapGenerator() {}
public:
	virtual void generateSector(Sector& sector, const VecXZ& pos) = 0;
};

