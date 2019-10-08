#include "stdafx.h"
#include "OverworldGenerator.h"

OverworldGenerator::OverworldGenerator()
	: m_seed(13213210),
	  m_biomeNoise(m_seed, {1, 1, 1000, 2, 2}),
	  m_fields(m_seed),
	  m_desert(m_seed)
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
					const auto& decorativeBlock = getCurrentBiome().getDecorativeBlock();
					if (decorativeBlock != BlockType::VOID) {
						srand(m_seed + pos.x * 2312321 * x * pos.z * 898009 * z);
						int r = rand() % 1000;
						if (r > 990) {
							chunk.setBlock(x, y, z, decorativeBlock);
						}
						depth = -1;
					}
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
