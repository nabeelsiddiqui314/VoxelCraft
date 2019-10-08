#pragma once
#include "MapGenerator.h"
#include "Noise.h"
#include "Biome.h"
#include "Fields.h"
#include "Desert.h"

class OverworldGenerator : public MapGenerator
{
public:
	OverworldGenerator();
public:
	virtual Chunks generateChunk(const VecXZ& pos) override;
private:
	const Biome& getCurrentBiome() const;
private:
	const std::uint32_t m_seed;
	Noise m_biomeNoise;
	Fields m_fields;
	Desert m_desert;
	float m_biomeVal;
};

