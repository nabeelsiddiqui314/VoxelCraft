#include "Biome.h"

Biome::Biome(const std::uint32_t seed, const NoiseProperties& properties, const std::vector<Composition::Layer>& layers)
	: m_heightMap(seed, properties), m_composition(layers)
{}

float Biome::getHeightAt(int x, int z) const {
	return applyFunctionTo(m_heightMap.getNoiseAt(x, z));
}

const Composition& Biome::getComposition() const {
	return m_composition;
}

float Biome::applyFunctionTo(float y) const {
	return y;
}
