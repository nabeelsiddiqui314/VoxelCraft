#include "stdafx.h"
#include "OverworldGenerator.h"

OverworldGenerator::OverworldGenerator() 
	: m_seed(10000), 
	  m_mt(m_rd()),
      m_random(0.0f, 1.0f) {
	m_mt.seed(m_seed);
}

ChunkBlocks OverworldGenerator::generateChunk(const VecXZ& pos) {
	ChunkBlocks chunk;

	std::int16_t height;

	for (std::int16_t x = 0; x < CHUNK_WIDTH; x++) {
		for (std::int16_t z = 0; z < CHUNK_WIDTH; z++) {
			height = 40 * getNoise(pos.x, pos.z, x, z);
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
	cx *= CHUNK_WIDTH;
	cz *= CHUNK_WIDTH;

	m_mt.seed(cx * 23213 + cz * 90988 + m_seed);
	float v1 = m_random(m_mt);

	m_mt.seed((cx + CHUNK_WIDTH) * 23213 + cz * 90988 + m_seed);
	float v2 = m_random(m_mt);

	m_mt.seed(cx * 23213 + (cz + CHUNK_WIDTH) * 90988 + m_seed);
	float v3 = m_random(m_mt);
	
	m_mt.seed((cx + CHUNK_WIDTH) * 23213 + (cz + CHUNK_WIDTH) * 90988 + m_seed);
	float v4 = m_random(m_mt);

	float i1 = v1 + (v2 - v1) * ((float)x / (float)CHUNK_WIDTH);
	float i2 = v3 + (v4 - v3) * ((float)x / (float)CHUNK_WIDTH);

	return i1 + (i2 - i1) * ((float)z / (float)CHUNK_WIDTH);
}
