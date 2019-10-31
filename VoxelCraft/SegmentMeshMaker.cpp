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
	const Segment* segment,
	const Segment* top, const Segment* bottom,
	const Segment* left, const Segment* right,
	const Segment* front, const Segment* back) {
	MeshGenerator solidMesh(meshes.solid.mesh);
	MeshGenerator liquidMesh(meshes.liquid.mesh);
	MeshGenerator floraMesh(meshes.flora.mesh);

	if (segment->isEmpty())
		return;
	if (top && bottom) {
		if (segment->isAllOpaque() && top->isAllOpaque() && bottom->isAllOpaque() &&
			left->isAllOpaque() && right->isAllOpaque() && front->isAllOpaque() &&
			back->isAllOpaque()) {
			return;
		}
	}

	std::array<Voxel::Element, 7> vxl;

	auto setNeighbors = [&](std::int16_t x, std::int16_t y, std::int16_t z) {
		vxl[VOXEL] = segment->getVoxel(x, y, z);

		// x
		if (x - 1 < 0)
			vxl[LEFT] = left->getVoxel(Segment::WIDTH - 1, y, z);
		else
			vxl[LEFT] = segment->getVoxel(x - 1, y, z);

		if (x + 1 >= Segment::WIDTH)
			vxl[RIGHT] = right->getVoxel(0, y, z);
		else
			vxl[RIGHT] = segment->getVoxel(x + 1, y, z);

		//z

		if (z - 1 < 0)
			vxl[BACK] = back->getVoxel(x, y, Segment::WIDTH - 1);
		else
			vxl[BACK] = segment->getVoxel(x, y, z - 1);

		if (z + 1 >= Segment::WIDTH)
			vxl[FRONT] = front->getVoxel(x, y, 0);
		else
			vxl[FRONT] = segment->getVoxel(x, y, z + 1);

		// y
		if (y - 1 < 0) {
			if (bottom == nullptr)
				vxl[BOTTOM] = Voxel::Type::VOID;
			else
				vxl[BOTTOM] = bottom->getVoxel(x, Segment::WIDTH - 1, z);
		}
		else
			vxl[BOTTOM] = segment->getVoxel(x, y - 1, z);

		if (y + 1 >= Segment::WIDTH) {
			if (top == nullptr)
				vxl[TOP] = Voxel::Type::VOID;
			else
				vxl[TOP] = top->getVoxel(x, 0, z);
		}
		else
			vxl[TOP] = segment->getVoxel(x, y + 1, z);
	};

	auto shouldAddCube = [&](int voxel) {
		return !vxl[voxel].getInfo().opaque;
	};

	auto shouldAddBlob = [&](int voxel) {
		if (vxl[VOXEL].getInfo().shaderType == Voxel::ShaderType::LIQUID) {
			if (voxel == TOP) {
				return vxl[VOXEL] != vxl[voxel].id; // for liquids dont cull opaque top sides.
			}
		}
		return !vxl[voxel].getInfo().opaque && vxl[VOXEL] != vxl[voxel].id;
	};

	for (std::int16_t x = 0; x < Segment::WIDTH; x++)
	for (std::int16_t y = 0; y < Segment::WIDTH; y++)
	for (std::int16_t z = 0; z < Segment::WIDTH; z++) {
		if (segment->getVoxel(x, y, z) == Voxel::Type::VOID)
			continue;
		setNeighbors(x, y, z);

		std::int16_t oX = x + originX;
		std::int16_t oY = y + originY;
		std::int16_t oZ = z + originZ;

		MeshGenerator* currentMesh = nullptr;
		switch (vxl[VOXEL].getInfo().shaderType) {
		case Voxel::ShaderType::SOLID:
			currentMesh = &solidMesh;
			break;
		case Voxel::ShaderType::LIQUID:
			currentMesh = &liquidMesh;
			break;
		case Voxel::ShaderType::FLORA:
			currentMesh = &floraMesh;
			break;
		}

		switch (vxl[VOXEL].getInfo().shape) {
		case Voxel::Shape::CUBE:
			if (shouldAddCube(TOP))
				currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texTop, s_top, s_topLight);

			if (shouldAddCube(BOTTOM))
				currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texBottom, s_bottom, s_bottomLight);

			if (shouldAddCube(LEFT))
				currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texSide, s_left, s_sideLight);

			if (shouldAddCube(RIGHT))
				currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texSide, s_right, s_sideLight);

			if (shouldAddCube(FRONT))
				currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texSide, s_front, s_sideLight);

			if (shouldAddCube(BACK))
				currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texSide, s_back, s_sideLight);
			break;
		case Voxel::Shape::BLOB:
			if (shouldAddBlob(TOP))
				currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texTop, s_top, s_topLight);

			if (shouldAddBlob(BOTTOM))
				currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texBottom, s_bottom, s_bottomLight);
												 
			if (shouldAddBlob(LEFT))			 
				currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texSide, s_left, s_sideLight);
												 
			if (shouldAddBlob(RIGHT))			 
				currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texSide, s_right, s_sideLight);
												 
			if (shouldAddBlob(FRONT))			 
				currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texSide, s_front, s_sideLight);
												 
			if (shouldAddBlob(BACK))			 
				currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texSide, s_back, s_sideLight);
			break;
		case Voxel::Shape::CROSS:
			currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texTop, s_crossA, s_topLight);
			currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texTop, s_crossB, s_topLight);
			break;
		}
	}
}