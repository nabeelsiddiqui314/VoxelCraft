#include "stdafx.h"
#include "Desert.h"


Desert::Desert(const std::uint32_t seed)
 : Biome(seed, getNoiseProperties(), getLayers()) {}

bool Desert::hasWater() const {
	return false;
}

Voxel::Type Desert::getDecorativeVoxel() const {
	return Voxel::Type::SHRUB;
}

NoiseProperties Desert::getNoiseProperties() const {
	NoiseProperties properties;
	properties.amplitude = 200;
	properties.smoothness = 90;
	properties.octaves = 2;
	properties.persistance = 5;
	properties.lacunarity = 5;
	return properties;
}

std::vector<Composition::Layer> Desert::getLayers() const {
	std::vector<Composition::Layer> layers;
	layers.emplace_back(std::make_pair(Voxel::Type::SAND, 0));
	return layers;
}

