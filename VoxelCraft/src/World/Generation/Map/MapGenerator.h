#pragma once

class Sector;
struct VecXZ;

class MapGenerator
{
public:
	virtual ~MapGenerator() {}
public:
	virtual void generateSector(Sector& sector, const VecXZ& pos) = 0;
};

