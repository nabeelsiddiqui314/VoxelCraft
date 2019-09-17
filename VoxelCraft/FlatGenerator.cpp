#include "stdafx.h"
#include "FlatGenerator.h"

FlatGenerator::FlatGenerator(std::int16_t height) : m_height(height) {}

ChunkBlocks FlatGenerator::generateChunk(const VecXZ& pos) {
	ChunkBlocks chunk;

	for (std::int16_t x = 0; x < CHUNK_WIDTH; x++) {
		for (std::int16_t z = 0; z < CHUNK_WIDTH; z++) {
			for (std::int16_t y = 0; y < m_height; y++) {
				if (y <= m_height - 5)
					chunk.setBlock(x, y, z, BlockType::STONE);
				else if (y <= m_height - 2)
					chunk.setBlock(x, y, z, BlockType::DIRT);
				else if (y == m_height - 1)
					chunk.setBlock(x, y, z, BlockType::GRASS);
			}
		}
	}
	return chunk;
}
