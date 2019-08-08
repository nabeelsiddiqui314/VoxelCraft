#include "stdafx.h"
#include "FlatGenerator.h"

Chunk FlatGenerator::generateChunk(const VecXZ& pos) {
	Chunk chunk;
	for (std::int16_t x = 0; x < CHUNK_WIDTH; x++) {
		for (std::int16_t y = 0; y < CHUNK_HEIGHT; y++) {
			for (std::int16_t z = 0; z < CHUNK_WIDTH; z++) {
				chunk.setBlock(x, y, z, BlockType::GRASS);
			}
		}
	}
	return chunk;
}
