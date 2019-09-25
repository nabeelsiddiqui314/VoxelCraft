#include "stdafx.h"
#include "SegmentMeshMaker.h"
#include "Segment.h"

// indices in 0, 1, 2, 0, 2, 3

const std::array<GLfloat, 12> SegmentMeshMaker::s_front = {
	0, 0, 0,
	1, 0, 0,
	1, 1, 0,
	0, 1, 0
};

const std::array<GLfloat, 12> SegmentMeshMaker::s_back = {
	1, 0, -1,
	0, 0, -1,
	0, 1, -1,
	1, 1, -1
};

const std::array<GLfloat, 12> SegmentMeshMaker::s_left = {
	0, 0, -1,
	0, 0,  0,
	0, 1,  0,
	0, 1, -1
};

const std::array<GLfloat, 12> SegmentMeshMaker::s_right = {
	1, 0,  0,
	1, 0, -1,
	1, 1, -1,
	1, 1,  0
};

const std::array<GLfloat, 12> SegmentMeshMaker::s_top = {
	0, 1,  0,
	1, 1,  0,
	1, 1, -1,
	0, 1, -1
};

const std::array<GLfloat, 12> SegmentMeshMaker::s_bottom = {
	0, 0, -1,
	1, 0, -1,
	1, 0,  0,
	0, 0,  0
};

SegmentMeshMaker::SegmentMeshMaker(MeshTypes& meshes, std::int16_t originX, std::int16_t originY, std::int16_t originZ,
	const Segment* chunk,
	const Segment* top, const Segment* bottom,
	const Segment* left, const Segment* right,
	const Segment* front, const Segment* back) {
	MeshGenerator solidMesh(meshes.solid.mesh);
	MeshGenerator waterMesh(meshes.water.mesh);

	if (chunk->isEmpty())
		return;
	if (top && bottom) {
		if (chunk->isAllOpaque() && top->isAllOpaque() && bottom->isAllOpaque() &&
			left->isAllOpaque() && right->isAllOpaque() && front->isAllOpaque() &&
			back->isAllOpaque()) {
			return;
		}
	}

	BlockType topB
		, bottomB
		, leftB
		, rightB
		, frontB
		, backB;

	auto setNeighbors = [&](std::int16_t x, std::int16_t y, std::int16_t z) {
		// x
		if (x - 1 < 0)
			leftB = left->getBlock(Segment::WIDTH - 1, y, z);
		else
			leftB = chunk->getBlock(x - 1, y, z);

		if (x + 1 >= Segment::WIDTH)
			rightB = right->getBlock(0, y, z);
		else
			rightB = chunk->getBlock(x + 1, y, z);

		//z

		if (z - 1 < 0)
			backB = back->getBlock(x, y, Segment::WIDTH - 1);
		else
			backB = chunk->getBlock(x, y, z - 1);

		if (z + 1 >= Segment::WIDTH)
			frontB = front->getBlock(x, y, 0);
		else
			frontB = chunk->getBlock(x, y, z + 1);

		// y
		if (y - 1 < 0) {
			if (bottom == nullptr)
				bottomB = BlockType::VOID;
			else
				bottomB = bottom->getBlock(x, Segment::WIDTH - 1, z);
		}
		else
			bottomB = chunk->getBlock(x, y - 1, z);

		if (y + 1 >= Segment::WIDTH) {
			if (top == nullptr)
				topB = BlockType::VOID;
			else
				topB = top->getBlock(x, 0, z);
		}
		else
			topB = chunk->getBlock(x, y + 1, z);
	};

	for (std::int16_t x = 0; x < Segment::WIDTH; x++) {
		for (std::int16_t y = 0; y < Segment::WIDTH; y++) {
			for (std::int16_t z = 0; z < Segment::WIDTH; z++) {
				if (chunk->getBlock(x, y, z) == BlockType::VOID)
					continue;
				setNeighbors(x, y, z);

				std::int16_t oX = x + originX;
				std::int16_t oY = y + originY;
				std::int16_t oZ = z + originZ;

				switch (BlockCodex::getBlockData(chunk->getBlock(x, y, z)).category) {
				case BlockCategory::SOLID:
					if (!BlockCodex::getBlockData(topB).opaque)
						solidMesh.addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texCoordTop, s_top);

					if (!BlockCodex::getBlockData(bottomB).opaque)
						solidMesh.addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texCoordBottom, s_bottom);

					if (!BlockCodex::getBlockData(leftB).opaque)
						solidMesh.addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texCoordSide, s_left);

					if (!BlockCodex::getBlockData(rightB).opaque)
						solidMesh.addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texCoordSide, s_right);

					if (!BlockCodex::getBlockData(frontB).opaque)
						solidMesh.addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texCoordSide, s_front);

					if (!BlockCodex::getBlockData(backB).opaque)
						solidMesh.addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texCoordSide, s_back);
					break;
				case BlockCategory::WATER:
					if (!BlockCodex::getBlockData(topB).opaque)
						solidMesh.addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texCoordTop, s_top);
					break;
				}
			}
		}
	}
}