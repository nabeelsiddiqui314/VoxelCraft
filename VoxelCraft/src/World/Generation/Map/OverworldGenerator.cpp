#include "OverworldGenerator.h"
#include <cstdint>
#include "../../../Math/vecXZ.h"
#include "../../../Math/FastRandom.h"
#include "../../Segment/Sector.h"
#include "../../Generation/Biome/Biome.h"

OverworldGenerator::OverworldGenerator()
	: m_seed(13213210),
	m_biomeNoise(m_seed, { 1, 1, 1000, 2, 2 }),
	m_fields(m_seed),
	m_desert(m_seed),
	m_oceans(m_seed),
	p_currentSquare(nullptr)
      {}

void OverworldGenerator::generateSector(Sector& sector, const VecXZ& pos) {
	std::int16_t height;

	setSquares(pos.x, pos.z);

	for (std::int16_t x = 0; x < Segment::WIDTH; x++) 
	for (std::int16_t z = 0; z < Segment::WIDTH; z++) {
		float biomeValue = m_biomeNoise.getNoiseAt(x + pos.x * Segment::WIDTH, z + pos.z * Segment::WIDTH);
		const auto& biome = getBiome(biomeValue);

		setCurrentSqare(x, z);
		if (p_currentSquare->shouldLerp) {
			height = getLerpedHeight(x, z);
		}
		else {
			height = biome.getHeightAt(x + pos.x * Segment::WIDTH, z + pos.z * Segment::WIDTH);
		}
		height = biome.applyFunctionTo(height);

		int depth = 0;
		for (int y = Sector::HEIGHT * Segment::WIDTH; y-- > 0;) {
			if (y <= height) {
				if (y == height) {
					auto decorativeVoxel = biome.getDecorativeVoxel();
					if (decorativeVoxel != Voxel::Type::VOID) {
						auto& random = FastRandom::get();

						random.seed(m_seed + pos.x * 2312321 * x * pos.z * 898009 * z);
						int r = random.random() % 1000;

						if (r > 990) {
							sector.setVoxel(x, y, z, decorativeVoxel);
						}
						depth = -1;
					}
				}
				else {
					sector.setVoxel(x, y, z, biome.getComposition().getVoxelAt(depth));
				}
				depth++;
			}
			if (biome.hasWater()) {
				if (y <= Sector::HEIGHT * Segment::WIDTH / 4) {
					if (sector.getVoxel(x, y, z) == Voxel::Type::VOID) {
						if (y <= Sector::HEIGHT * Segment::WIDTH / 4 - 3)
							sector.setVoxel(x, y, z, Voxel::Type::WATER);
					}
					else {
						sector.setVoxel(x, y, z, Voxel::Type::SAND);
					}
				}
			}
		}
	}
}

const Biome& OverworldGenerator::getBiome(float biomeValue) const {
	if (biomeValue < 0.6f)
		return m_fields;
	else if (biomeValue < 0.9f)
		return m_oceans;
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
	static const float sectorHeight = Segment::WIDTH * Sector::HEIGHT;

	int cx = x * Segment::WIDTH;
	int cz = z * Segment::WIDTH;

	auto makeSquare = [&](LerpSqaure& sq, int ox, int oz) {
		int X = cx + ox * width;
		int Z = cz + oz * width;

		const auto* x1min = &getBiome(m_biomeNoise.getNoiseAt(X, Z));
		const auto*	x1max = &getBiome(m_biomeNoise.getNoiseAt(X + width, Z));
		const auto*	x2min = &getBiome(m_biomeNoise.getNoiseAt(X, Z + width));
		const auto*	x2max = &getBiome(m_biomeNoise.getNoiseAt(X + width, Z + width));

		sq.shouldLerp = x1min != x1max || x2min != x2max || x1min != x2max;
		if (sq.shouldLerp) {
			sq.x1min = x1min->getHeightAt(X, Z) / sectorHeight;
			sq.x1max = x1max->getHeightAt(X + width, Z) / sectorHeight;
			sq.x2min = x2min->getHeightAt(X, Z + width) / sectorHeight;
			sq.x2max = x2max->getHeightAt(X + width, Z + width) / sectorHeight;
		}
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

float OverworldGenerator::getLerpedHeight(float x, float z) {
	static const float sectorHeight = Segment::WIDTH * Sector::HEIGHT;
	static const int width = Segment::WIDTH / 2;

	x = (int)x % width;
	z = (int)z % width;

	x /= (float)width;
	z /= (float)width;

	return biLerp(x, z, p_currentSquare->x1min, p_currentSquare->x1max,
		p_currentSquare->x2min, p_currentSquare->x2max) * sectorHeight;
}
