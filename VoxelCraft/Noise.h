#pragma once
#include <random>

struct NoiseProperties {
	float amplitude;
	float persistance;
	float lacunarity;
	float octaves;
	float smoothness;
};

class Noise
{
private:
	struct vec {
		float x, z;
	};
public:
	Noise();
public:
	void setProperties(const NoiseProperties& properties);
	float getOctaveNoise(float x, float z);
	float getNoiseAt(float x, float z);
private:
	float dot(const vec& v1, const vec& v2);
	float lerp(float x, float a, float b);
	float fade(float t);
private:
	const std::uint32_t m_seed;
	std::random_device m_rd;
	std::mt19937 m_mt;
	std::uniform_int_distribution<int> m_random;
	NoiseProperties m_properties;
};