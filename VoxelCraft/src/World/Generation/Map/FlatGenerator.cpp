#include "FlatGenerator.h"
#include "../../Segment/SegmentStack.h"

FlatGenerator::FlatGenerator(std::int16_t height) : m_height(height) {}

void FlatGenerator::generateStack(SegmentStack& stack, int x, int z) {
	for (std::int16_t x = 0; x < Segment::WIDTH; x++) {
		for (std::int16_t z = 0; z < Segment::WIDTH; z++) {
			for (std::int16_t y = 0; y < m_height; y++) {
				if (y <= m_height - 5)
					stack.setVoxel(x, y, z, Voxel::Type::STONE);
				else if (y <= m_height - 2)
					stack.setVoxel(x, y, z, Voxel::Type::DIRT);
				else
					stack.setVoxel(x, y, z, Voxel::Type::GRASS);
			}
		}
	}
}
