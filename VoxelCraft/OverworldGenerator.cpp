#include "stdafx.h"
#include "OverworldGenerator.h"

OverworldGenerator::OverworldGenerator() 
	: m_biomeNoise(13213210, {1, 1, 1000, 2, 2}),
	  m_fields(13213210),
	  m_desert(13213210)
      {}

Chunks OverworldGenerator::generateChunk(const VecXZ& pos) {
	Chunks chunk;
	std::int16_t height;
    m_biomeVal = m_biomeNoise.getNoiseAt(pos.x * Segment::WIDTH, pos.z * Segment::WIDTH);

	for (std::int16_t x = 0; x < Segment::WIDTH; x++) 
	for (std::int16_t z = 0; z < Segment::WIDTH; z++) {
		height = getCurrentBiome().getHeightAt(x + pos.x * Segment::WIDTH, z + pos.z * Segment::WIDTH);
		int depth = 0;

		for (int y = Chunks::HEIGHT * Segment::WIDTH; y-- > 0;) {
			if (y <= height) {
				if (y == height) {
					int r = rand() % 100;
					if (m_biomeVal < 0.6f) {
						if(r > 80)
							chunk.setBlock(x, y, z, BlockType::ROSE);
					}
					else {
						if (r > 90)
							chunk.setBlock(x, y, z, BlockType::SHRUB);
					}
					depth = -1;
				}
				else {
					chunk.setBlock(x, y, z, getCurrentBiome().getComposition().getBlockAt(depth));
				}
				depth++;
			}
			if (getCurrentBiome().hasWater()) {
				if (y <= Chunks::HEIGHT * Segment::WIDTH / 4) {
					if (chunk.getBlock(x, y, z) == BlockType::VOID) {
						if (y <= Chunks::HEIGHT * Segment::WIDTH / 4 - 3)
							chunk.setBlock(x, y, z, BlockType::WATER);
					}
					else {
						chunk.setBlock(x, y, z, BlockType::SAND);
					}
				}
			}
		}
	}
	return chunk;
}

const Biome& OverworldGenerator::getCurrentBiome() const {
	if (m_biomeVal < 0.6f)
		return m_fields;
	else
		return m_desert;
}
