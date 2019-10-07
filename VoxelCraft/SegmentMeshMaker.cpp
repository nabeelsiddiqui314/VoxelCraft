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

const std::array<GLfloat, 12> SegmentMeshMaker::s_crossA = {
	0, 0, -1,
	1, 0,  0,
	1, 1,  0,
	0, 1, -1
};

const std::array<GLfloat, 12> SegmentMeshMaker::s_crossB = {
	1, 0, -1,
	0, 0,  0,
	0, 1,  0,
	1, 1, -1
};

const GLfloat SegmentMeshMaker::s_topLight = 1.0f;
const GLfloat SegmentMeshMaker::s_sideLight = 0.6f;
const GLfloat SegmentMeshMaker::s_bottomLight = 0.4f;

SegmentMeshMaker::SegmentMeshMaker(MeshTypes& meshes, std::int16_t originX, std::int16_t originY, std::int16_t originZ,
	const Segment* chunk,
	const Segment* top, const Segment* bottom,
	const Segment* left, const Segment* right,
	const Segment* front, const Segment* back) {
	MeshGenerator solidMesh(meshes.solid.mesh);
	MeshGenerator liquidMesh(meshes.liquid.mesh);
	MeshGenerator floraMesh(meshes.flora.mesh);

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

				MeshGenerator* currentMesh = nullptr;
				switch (BlockCodex::getBlockData(chunk->getBlock(x, y, z)).shaderType) {
				case ShaderType::SOLID:
					currentMesh = &solidMesh;
					break;
				case ShaderType::LIQUID:
					currentMesh = &liquidMesh;
					break;
				case ShaderType::FLORA:
					currentMesh = &floraMesh;
					break;
				}

				switch (BlockCodex::getBlockData(chunk->getBlock(x, y, z)).shape) {
				case BlockShape::CUBE:
					if (!BlockCodex::getBlockData(topB).opaque)
						currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texTop, s_top, s_topLight);

					if (!BlockCodex::getBlockData(bottomB).opaque)
						currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texBottom, s_bottom, s_bottomLight);

					if (!BlockCodex::getBlockData(leftB).opaque)
						currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texSide, s_left, s_sideLight);

					if (!BlockCodex::getBlockData(rightB).opaque)
						currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texSide, s_right, s_sideLight);

					if (!BlockCodex::getBlockData(frontB).opaque)
						currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texSide, s_front, s_sideLight);

					if (!BlockCodex::getBlockData(backB).opaque)
						currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texSide, s_back, s_sideLight);
					break;
				case BlockShape::PLANE:
					if (topB == BlockType::VOID)
						currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texTop, s_top, s_topLight);
					break;
				case BlockShape::CROSS:
					if (!BlockCodex::getBlockData(frontB).opaque || !BlockCodex::getBlockData(backB).opaque  ||
						!BlockCodex::getBlockData(leftB).opaque  || !BlockCodex::getBlockData(rightB).opaque ||
						!BlockCodex::getBlockData(topB).opaque   || !BlockCodex::getBlockData(bottomB).opaque) {
						currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texTop, s_crossA, s_topLight);
						currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texTop, s_crossB, s_topLight);
					}
					break;
				}
			}
		}
	}
}