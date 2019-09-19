#pragma once
#include "MapGenerator.h"
#include <random>

class OverworldGenerator : public MapGenerator
{
public:
	OverworldGenerator();
public:
	virtual Chunks generateChunk(const VecXZ& pos) override;
private:
	float getNoise(int cx, int cz, float x, float z);
private:
	const std::uint32_t m_seed;
	std::random_device m_rd;
	std::mt19937 m_mt;
	std::uniform_real_distribution<float> m_random;
};

