#include "stdafx.h"
#include "OverworldGenerator.h"

OverworldGenerator::OverworldGenerator() 
	: m_biomeNoise(13213210, {1, 1, 1000, 2, 2})
      {
	m_desert = std::make_shared<Desert>(13213210);
	m_fields = std::make_shared<Fields>(13213210);
}

Chunks OverworldGenerator::generateChunk(const VecXZ& pos) {
	Chunks chunk;

	std::int16_t height;

	for (std::int16_t x = 0; x < Segment::WIDTH; x++) {
		for (std::int16_t z = 0; z < Segment::WIDTH; z++) {
			m_biomeVal = m_biomeNoise.getNoiseAt(x + pos.x * Segment::WIDTH, z + pos.z * Segment::WIDTH);
			height = getCurrentBiome()->getHeightAt(x + pos.x * Segment::WIDTH, z + pos.z * Segment::WIDTH);

			int depth = 0;
			for (int y = height; y-- > 0;) {
				chunk.setBlock(x, y, z, getCurrentBiome()->getComposition().getBlockAt(depth));
				depth++;
			}
			if (getCurrentBiome()->hasWater()) {
				for (std::int16_t y = 0; y < Chunks::HEIGHT * Segment::WIDTH; y++) {
					if (y <= Chunks::HEIGHT * Segment::WIDTH / 4) {
						switch (BlockCodex::getBlockData(chunk.getBlock(x, y, z)).category) {
						case BlockCategory::NONE:
							if (y <= Chunks::HEIGHT * Segment::WIDTH / 4 - 3)
								chunk.setBlock(x, y, z, BlockType::WATER);
							break;
						case BlockCategory::SOLID:
							chunk.setBlock(x, y, z, BlockType::SAND);
							break;
						}
					}
				}
			}
		}
	}
	return chunk;
}

const std::shared_ptr<Biome> OverworldGenerator::getCurrentBiome() const {
	if (m_biomeVal < 0.6f)
		return m_fields;
	else
		return m_desert;
}
