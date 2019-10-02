#include "stdafx.h"
#include "OverworldGenerator.h"

OverworldGenerator::OverworldGenerator() {
	m_properties.amplitude = 150;
	m_properties.smoothness = 70;
	m_properties.octaves = 5;
	m_properties.persistance = 4;
	m_properties.lacunarity = 4;
	m_noise.setProperties(m_properties);
}

Chunks OverworldGenerator::generateChunk(const VecXZ& pos) {
	Chunks chunk;

	std::int16_t height;

	for (std::int16_t x = 0; x < Segment::WIDTH; x++) {
		for (std::int16_t z = 0; z < Segment::WIDTH; z++) {
			height = m_noise.getOctaveNoise(x + pos.x * Segment::WIDTH, z + pos.z * Segment::WIDTH);
			for (std::int16_t y = 0; y < height; y++) {
				if (y <= height) {
					if (y <= height - 5)
						chunk.setBlock(x, y, z, BlockType::STONE);
					else if (y <= height - 2)
						chunk.setBlock(x, y, z, BlockType::DIRT);
					else if (y == height - 1)
						chunk.setBlock(x, y, z, BlockType::GRASS);
				}
			}
			for(std::int16_t y = 0; y < Chunks::HEIGHT * Segment::WIDTH; y++) {
				if (y <= Chunks::HEIGHT * Segment::WIDTH / 4) {
					switch (BlockCodex::getBlockData(chunk.getBlock(x, y, z)).category) {
					case BlockCategory::NONE:
						if(y <= Chunks::HEIGHT * Segment::WIDTH / 4 - 3)
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
	return chunk;
}