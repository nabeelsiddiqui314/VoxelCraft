#include "stdafx.h"
#include "OverworldGenerator.h"

OverworldGenerator::OverworldGenerator()
	: m_seed(13213210),
	m_biomeNoise(m_seed, { 1, 1, 1000, 2, 2 }),
	m_fields(m_seed),
	m_desert(m_seed),
	p_currentSquare(nullptr)
      {}

Chunks OverworldGenerator::generateChunk(const VecXZ& pos) {
	Chunks chunk;
	std::int16_t height;

	setSquares(pos.x, pos.z);

	for (std::int16_t x = 0; x < Segment::WIDTH; x++) 
	for (std::int16_t z = 0; z < Segment::WIDTH; z++) {
		float biomeValue = m_biomeNoise.getNoiseAt(x + pos.x * Segment::WIDTH, z + pos.z * Segment::WIDTH);
		const auto& biome = getBiome(biomeValue);

		height = getHeight(x, z);

		int depth = 0;
		for (int y = Chunks::HEIGHT * Segment::WIDTH; y-- > 0;) {
			if (y <= height) {
				if (y == height) {
					const auto& decorativeBlock = biome.getDecorativeBlock();
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
					chunk.setBlock(x, y, z, biome.getComposition().getBlockAt(depth));
				}
				depth++;
			}
			if (biome.hasWater()) {
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

const Biome& OverworldGenerator::getBiome(float biomeValue) const {
	if (biomeValue < 0.6f)
		return m_fields;
	else
		return m_desert;
}

float OverworldGenerator::biLerp(float x, float z, float x1min, float x1max, float x2min, float x2max) {
	float x1 = x1min + x * (x1max - x1min);
	float x2 = x2min + x * (x2max - x2min);
	return x1 + z * (x2 - x1);
}

void OverworldGenerator::setSquares(int x, int z) {
	static const int width = Segment::WIDTH / 2;
	static const float chunkHeight = Segment::WIDTH * Chunks::HEIGHT;

	int cx = x * Segment::WIDTH;
	int cz = z * Segment::WIDTH;

	auto makeSquare = [&](LerpSqaure& sq, int ox, int oz) {
		int X = cx + ox * width;
		int Z = cz + oz * width;

		sq.x1min = getBiome(m_biomeNoise.getNoiseAt(X, Z)).getHeightAt(X, Z) / chunkHeight;
		sq.x1max = getBiome(m_biomeNoise.getNoiseAt(X + width, Z)).getHeightAt(X + width, Z) / chunkHeight;

		sq.x2min = getBiome(m_biomeNoise.getNoiseAt(X, Z + width)).getHeightAt(X, Z + width) / chunkHeight;
		sq.x2max = getBiome(m_biomeNoise.getNoiseAt(X + width, Z + width)).getHeightAt(X + width, Z + width) / chunkHeight;
	};

	makeSquare(m_topLeft, 0, 0);
	makeSquare(m_topRight, 1, 0);
	makeSquare(m_bottomLeft, 0, 1);
	makeSquare(m_bottomRight, 1, 1);
}

void OverworldGenerator::setCurrentSqare(int x, int z) {
	static const int width = Segment::WIDTH / 2;

	if (x < width && z < width) {
		p_currentSquare = &m_topLeft;
	}
	else if (x >= width && z >= width) {
		p_currentSquare = &m_bottomRight;
	}
	else if (x >= width && z < width) {
		p_currentSquare = &m_topRight;
	}
	else {
		p_currentSquare = &m_bottomLeft;
	}
}

float OverworldGenerator::getHeight(float x, float z) {
	static const float chunkHeight = Segment::WIDTH * Chunks::HEIGHT;
	static const int width = Segment::WIDTH / 2;

	setCurrentSqare(x, z);
	x = (int)x % width;
	z = (int)z % width;

	x /= (float)width;
	z /= (float)width;

	return biLerp(x, z, p_currentSquare->x1min, p_currentSquare->x1max,
		p_currentSquare->x2min, p_currentSquare->x2max) * chunkHeight;
}
