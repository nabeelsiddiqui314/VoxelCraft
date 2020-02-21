#pragma once
#include "FastRandom.h"
#include <cstdint>
#include <cmath>

struct NoiseProperties {
	float octaves;
	float amplitude;
	float smoothness;
	float persistance;
	float lacunarity;
};

class Noise
{
private:
	struct vec {
		float x, z;
	};
public:
	Noise(const std::uint32_t seed, const NoiseProperties& properties);
public:
	float getNoiseAt(float x, float z) const;
private:
	float getBasicNoise(float x, float z) const;
	float dot(const vec& v1, const vec& v2) const;
	float lerp(float x, float a, float b) const;
	float fade(float t) const;
private:
	const std::uint32_t m_seed;
	NoiseProperties m_properties;
};