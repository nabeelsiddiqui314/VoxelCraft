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

	std::array<BlockType, 7> blk;

	auto setNeighbors = [&](std::int16_t x, std::int16_t y, std::int16_t z) {
		blk[BLOCK] = chunk->getBlock(x, y, z);

		// x
		if (x - 1 < 0)
			blk[LEFT] = left->getBlock(Segment::WIDTH - 1, y, z);
		else
			blk[LEFT] = chunk->getBlock(x - 1, y, z);

		if (x + 1 >= Segment::WIDTH)
			blk[RIGHT] = right->getBlock(0, y, z);
		else
			blk[RIGHT] = chunk->getBlock(x + 1, y, z);

		//z

		if (z - 1 < 0)
			blk[BACK] = back->getBlock(x, y, Segment::WIDTH - 1);
		else
			blk[BACK] = chunk->getBlock(x, y, z - 1);

		if (z + 1 >= Segment::WIDTH)
			blk[FRONT] = front->getBlock(x, y, 0);
		else
			blk[FRONT] = chunk->getBlock(x, y, z + 1);

		// y
		if (y - 1 < 0) {
			if (bottom == nullptr)
				blk[BOTTOM] = BlockType::VOID;
			else
				blk[BOTTOM] = bottom->getBlock(x, Segment::WIDTH - 1, z);
		}
		else
			blk[BOTTOM] = chunk->getBlock(x, y - 1, z);

		if (y + 1 >= Segment::WIDTH) {
			if (top == nullptr)
				blk[TOP] = BlockType::VOID;
			else
				blk[TOP] = top->getBlock(x, 0, z);
		}
		else
			blk[TOP] = chunk->getBlock(x, y + 1, z);
	};

	auto shouldAddCube = [&](int block) {
		return !BlockCodex::getBlockData(blk[block]).opaque;
	};

	auto shouldAddBlob = [&](int block) {
		if (BlockCodex::getBlockData(blk[BLOCK]).shaderType == ShaderType::LIQUID) {
			if (block == TOP) {
				return blk[BLOCK] != blk[block]; // for liquids dont cull opaque top sides.
			}
		}
		return !BlockCodex::getBlockData(blk[block]).opaque && blk[BLOCK] != blk[block];
	};

	for (std::int16_t x = 0; x < Segment::WIDTH; x++)
	for (std::int16_t y = 0; y < Segment::WIDTH; y++)
	for (std::int16_t z = 0; z < Segment::WIDTH; z++) {
		if (chunk->getBlock(x, y, z) == BlockType::VOID)
			continue;
		setNeighbors(x, y, z);

		std::int16_t oX = x + originX;
		std::int16_t oY = y + originY;
		std::int16_t oZ = z + originZ;

		MeshGenerator* currentMesh = nullptr;
		switch (BlockCodex::getBlockData(blk[BLOCK]).shaderType) {
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

		switch (BlockCodex::getBlockData(blk[BLOCK]).shape) {
		case BlockShape::CUBE:
			if (shouldAddCube(TOP))
				currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(blk[BLOCK]).texTop, s_top, s_topLight);

			if (shouldAddCube(BOTTOM))
				currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(blk[BLOCK]).texBottom, s_bottom, s_bottomLight);

			if (shouldAddCube(LEFT))
				currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(blk[BLOCK]).texSide, s_left, s_sideLight);

			if (shouldAddCube(RIGHT))
				currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(blk[BLOCK]).texSide, s_right, s_sideLight);

			if (shouldAddCube(FRONT))
				currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(blk[BLOCK]).texSide, s_front, s_sideLight);

			if (shouldAddCube(BACK))
				currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(blk[BLOCK]).texSide, s_back, s_sideLight);
			break;
		case BlockShape::BLOB:
			if (shouldAddBlob(TOP))
				currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texTop, s_top, s_topLight);

			if (shouldAddBlob(BOTTOM))
				currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texBottom, s_bottom, s_bottomLight);

			if (shouldAddBlob(LEFT))
				currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texSide, s_left, s_sideLight);

			if (shouldAddBlob(RIGHT))
				currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texSide, s_right, s_sideLight);

			if (shouldAddBlob(FRONT))
				currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texSide, s_front, s_sideLight);

			if (shouldAddBlob(BACK))
				currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(chunk->getBlock(x, y, z)).texSide, s_back, s_sideLight);
			break;
		case BlockShape::CROSS:
			currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(blk[BLOCK]).texTop, s_crossA, s_topLight);
			currentMesh->addFace(oX, oY, oZ, BlockCodex::getBlockData(blk[BLOCK]).texTop, s_crossB, s_topLight);
			break;
		}
	}
}