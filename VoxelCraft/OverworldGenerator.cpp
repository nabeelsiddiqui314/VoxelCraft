#include "stdafx.h"
#include "OverworldGenerator.h"

OverworldGenerator::OverworldGenerator() 
	: m_seed(10000), 
	  m_mt(m_rd()),
      m_random(0.0f, 1.0f) {
	m_mt.seed(m_seed);
}

Chunks OverworldGenerator::generateChunk(const VecXZ& pos) {
	Chunks chunk;

	std::int16_t height;

	for (std::int16_t x = 0; x < Segment::WIDTH; x++) {
		for (std::int16_t z = 0; z < Segment::WIDTH; z++) {
			height = 100 + 150 * (getNoise(pos.x, pos.z, x, z));
			for (std::int16_t y = 0; y < height; y++) {
				if (y <= height - 5)
					chunk.setBlock(x, y, z, BlockType::STONE);
				else if (y <= height - 2)
					chunk.setBlock(x, y, z, BlockType::DIRT);
				else if (y == height - 1)
					chunk.setBlock(x, y, z, BlockType::GRASS);
			}
		}
	}
	return chunk;
}

float OverworldGenerator::getNoise(int cx, int cz, float x, float z) {
	cx *= Segment::WIDTH;
	cz *= Segment::WIDTH;

	m_mt.seed(cx * 23213 + cz * 90988 + m_seed);
	float v1 = m_random(m_mt);

	m_mt.seed((cx + Segment::WIDTH) * 23213 + cz * 90988 + m_seed);
	float v2 = m_random(m_mt);

	m_mt.seed(cx * 23213 + (cz + Segment::WIDTH) * 90988 + m_seed);
	float v3 = m_random(m_mt);
	
	m_mt.seed((cx + Segment::WIDTH) * 23213 + (cz + Segment::WIDTH) * 90988 + m_seed);
	float v4 = m_random(m_mt);

	float i1 = v1 + (v2 - v1) * ((float)x / (float)Segment::WIDTH);
	float i2 = v3 + (v4 - v3) * ((float)x / (float)Segment::WIDTH);

	return i1 + (i2 - i1) * ((float)z / (float)Segment::WIDTH);
}
