#pragma once
#include "Noise.h"
#include "Composition.h"

class Biome
{
public:
	Biome(const std::uint32_t seed, const NoiseProperties& properties, const std::vector<Composition::Layer>& layers);
	virtual ~Biome() {}
public:
	float getHeightAt(int x, int z) const;
	const Composition& getComposition() const;
protected:
	virtual NoiseProperties getNoiseProperties() const = 0;
	virtual std::vector<Composition::Layer> getLayers() const = 0;
private:
	Noise m_heightMap;
	Composition m_composition;
};

