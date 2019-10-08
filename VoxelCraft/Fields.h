#pragma once
#include "Biome.h"

class Fields : public Biome
{
public:
	Fields(const std::uint32_t seed);
public:
	bool hasWater() const override;
	BlockType getDecorativeBlock() const override;
protected:
	NoiseProperties getNoiseProperties() const override;
	std::vector<Composition::Layer> getLayers() const override;
};

