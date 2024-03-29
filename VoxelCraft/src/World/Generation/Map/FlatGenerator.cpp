#include "FlatGenerator.h"
#include "../../Segment/Sector.h"

FlatGenerator::FlatGenerator(std::int16_t height) : m_height(height) {}

void FlatGenerator::generateSector(Sector& sector, const VecXZ& pos) {
	for (std::int16_t x = 0; x < Segment::WIDTH; x++) {
		for (std::int16_t z = 0; z < Segment::WIDTH; z++) {
			for (std::int16_t y = 0; y < m_height; y++) {
				if (y <= m_height - 5)
					sector.setVoxel(x, y, z, Voxel::Type::STONE);
				else if (y <= m_height - 2)
					sector.setVoxel(x, y, z, Voxel::Type::DIRT);
				else
					sector.setVoxel(x, y, z, Voxel::Type::GRASS);
			}
		}
	}
}
