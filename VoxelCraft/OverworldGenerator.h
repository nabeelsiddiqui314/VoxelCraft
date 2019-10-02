#pragma once
#include "MapGenerator.h"
#include "Noise.h"
#include "Biome.h"
#include "Fields.h"

class OverworldGenerator : public MapGenerator
{
public:
	OverworldGenerator();
public:
	virtual Chunks generateChunk(const VecXZ& pos) override;
private:
	const Biome* getBiome() const;
private:
	Noise m_biomeNoise;
	Fields m_fields;
};

