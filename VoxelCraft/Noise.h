#pragma once
#include <random>

class Noise
{
private:
	struct vec {
		float x, z;
	};
public:
	Noise();
public:
	float getOctaveNoise(int wx, int wz, int lx, int lz, int width);
	float getNoiseAt(int wx, int wz, int lx, int lz, int width, int stretching);
private:
	float dot(const vec& v1, const vec& v2);
	float lerp(float x, float a, float b);
	float fade(float t);
private:
	const std::uint32_t m_seed;
	std::random_device m_rd;
	std::mt19937 m_mt;
	std::uniform_int_distribution<int> m_random;
};