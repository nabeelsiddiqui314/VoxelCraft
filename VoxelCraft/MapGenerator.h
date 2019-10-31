#pragma once
#include "Sector.h"
#include "vecXZ.h"

class MapGenerator
{
public:
	virtual ~MapGenerator() {}
public:
	virtual Sector generateSector(const VecXZ& pos) = 0;
};

