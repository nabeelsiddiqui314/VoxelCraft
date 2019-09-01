#include "stdafx.h"
#include "FlatGenerator.h"

ChunkBlocks FlatGenerator::generateChunk(const VecXZ& pos) {
	ChunkBlocks chunk;
	for (std::int16_t x = 0; x < CHUNK_WIDTH; x++) {
		for (std::int16_t y = 0; y < CHUNK_HEIGHT; y++) {
			for (std::int16_t z = 0; z < CHUNK_WIDTH; z++) {
				if (pos.x == 0 || pos.z == 0 || pos.x ==9 || pos.z==9)
					chunk.setBlock(x, y, z, BlockType::VOID);
				else
					chunk.setBlock(x, y, z, BlockType::GRASS);
			}
		}
	}
	return chunk;
}
