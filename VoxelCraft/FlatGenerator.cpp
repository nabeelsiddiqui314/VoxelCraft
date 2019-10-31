#include "stdafx.h"
#include "FlatGenerator.h"

FlatGenerator::FlatGenerator(std::int16_t height) : m_height(height) {}

Sector FlatGenerator::generateSector(const VecXZ& pos) {
	Sector sector;

	for (std::int16_t x = 0; x < Segment::WIDTH; x++) {
		for (std::int16_t z = 0; z < Segment::WIDTH; z++) {
			for (std::int16_t y = 0; y < m_height; y++) {
				if (y <= m_height - 5)
					sector.setBlock(x, y, z, BlockType::STONE);
				else if (y <= m_height - 2)
					sector.setBlock(x, y, z, BlockType::DIRT);
				else
					sector.setBlock(x, y, z, BlockType::GRASS);
			}
		}
	}
	return sector;
}
