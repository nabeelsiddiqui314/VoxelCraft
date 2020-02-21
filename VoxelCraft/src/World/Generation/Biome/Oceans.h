#pragma once
#include "Biome.h"

class Oceans : public Biome
{
public:
	Oceans(const std::uint32_t seed);
	~Oceans() = default;
public:
	bool hasWater() const override;
	Voxel::Type getDecorativeVoxel() const override;
protected:
	NoiseProperties getNoiseProperties() const override;
	std::vector<Composition::Layer> getLayers() const override;
};

