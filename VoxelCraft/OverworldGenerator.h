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
	const std::shared_ptr<Biome> getCurrentBiome() const;
private:
	Noise m_biomeNoise;
	std::shared_ptr<Fields> m_fields;
	std::shared_ptr<Desert> m_desert;
	float m_biomeVal;
};

