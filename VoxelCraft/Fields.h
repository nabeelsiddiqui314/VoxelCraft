#pragma once
#include "Biome.h"

class Fields : public Biome
{
public:
	Fields(const std::uint32_t seed);
protected:
	NoiseProperties getNoiseProperties() const override;
	std::vector<Composition::Layer> getLayers() const override;
};

