#include "stdafx.h"
#include "FlatGenerator.h"

ChunkBlocks FlatGenerator::generateChunk(const VecXZ& pos) {
	ChunkBlocks chunk;
	if (pos.x == 0 || pos.z == 0 || pos.x == 10 || pos.z == 10)
		return chunk;

	for (std::int16_t x = 0; x < CHUNK_WIDTH; x++) {
		for (std::int16_t z = 0; z < CHUNK_WIDTH; z++) {
			std::int16_t height;
			if (rand() % 2 == 0)
				height = CHUNK_HEIGHT;
			else
				height = CHUNK_HEIGHT - 1;
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
