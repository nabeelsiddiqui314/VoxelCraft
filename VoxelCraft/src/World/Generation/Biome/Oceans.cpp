#include "Oceans.h"

Oceans::Oceans(const std::uint32_t seed) 
	: Biome(seed, getNoiseProperties(), getLayers()) {}

bool Oceans::hasWater() const {
	return true;
}

Voxel::Type Oceans::getDecorativeVoxel() const {
	return Voxel::Type::DIRT;
}

NoiseProperties Oceans::getNoiseProperties() const {
	NoiseProperties properties;
	properties.amplitude = 20;
	properties.smoothness = 20;
	properties.octaves = 2;
	properties.persistance = 4;
	properties.lacunarity = 4;
	return properties;
}

std::vector<Composition::Layer> Oceans::getLayers() const {
	std::vector<Composition::Layer> layers;
	layers.emplace_back(std::make_pair(Voxel::Type::SAND, 0));
	return layers;
}
