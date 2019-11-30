#pragma once
#include "MapGenerator.h"
#include "Noise.h"
#include "Biome.h"
#include "Fields.h"
#include "Desert.h"
#include "Oceans.h"

class OverworldGenerator : public MapGenerator
{
private:
	struct LerpSqaure {
		float x1min, x1max, x2min, x2max;
		bool shouldLerp;
	};
public:
	OverworldGenerator();
public:
	virtual void generateSector(Sector& sector, const VecXZ& pos) override;
private:
	const Biome& getBiome(float biomeValue) const;
	float biLerp(float x, float z, float x1min, float x1max, float x2min, float x2max);
	void setSquares(int x, int z);
	void setCurrentSqare(int x, int z);
	float getLerpedHeight(float x, float z);
private:
	const std::uint32_t m_seed;
	Noise m_biomeNoise;

	Fields m_fields;
	Desert m_desert;
	Oceans m_oceans;

	LerpSqaure m_topLeft;
	LerpSqaure m_topRight;
	LerpSqaure m_bottomLeft;
	LerpSqaure m_bottomRight;
	LerpSqaure* p_currentSquare;
};

