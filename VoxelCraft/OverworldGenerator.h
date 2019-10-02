#pragma once
#include "MapGenerator.h"
#include "Noise.h"

class OverworldGenerator : public MapGenerator
{
public:
	OverworldGenerator();
public:
	virtual Chunks generateChunk(const VecXZ& pos) override;
private:
	Noise m_noise;
	NoiseProperties m_properties;
};

