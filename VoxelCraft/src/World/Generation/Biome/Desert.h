#pragma once
#include "Biome.h"

class Desert : public Biome
{
public:
	Desert(const std::uint32_t seed);
public:
	bool hasWater() const override;
	Voxel::Type getDecorativeVoxel() const override;
protected:
	NoiseProperties getNoiseProperties() const override;
	std::vector<Composition::Layer> getLayers() const override;
};

