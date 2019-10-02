#include "stdafx.h"
#include "Fields.h"


Fields::Fields(const std::uint32_t seed) : Biome(seed, getNoiseProperties(), getLayers()) {}

bool Fields::hasWater() const {
	return true;
}

NoiseProperties Fields::getNoiseProperties() const {
	NoiseProperties properties;
	properties.amplitude = 150;
	properties.smoothness = 70;
	properties.octaves = 2;
	properties.persistance = 4;
	properties.lacunarity = 4;
	return properties;
}

std::vector<Composition::Layer> Fields::getLayers() const {
	std::vector<Composition::Layer> layers;
	layers.emplace_back(std::make_pair(BlockType::GRASS, 1));
	layers.emplace_back(std::make_pair(BlockType::DIRT, 3));
	layers.emplace_back(std::make_pair(BlockType::STONE, 0));
	return layers;
}
