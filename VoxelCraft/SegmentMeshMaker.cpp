#include "stdafx.h"
#include "SegmentMeshMaker.h"
#include "Segment.h"
#include "SegmentBounds.h"

// indices in 0, 1, 2, 0, 2, 3

SegmentMeshMaker::Face SegmentMeshMaker::s_front = {
	0, 0, 0,
	1, 0, 0,
	1, 1, 0,
	0, 1, 0
};

SegmentMeshMaker::Face SegmentMeshMaker::s_back = {
	1, 0, -1,
	0, 0, -1,
	0, 1, -1,
	1, 1, -1
};

SegmentMeshMaker::Face SegmentMeshMaker::s_left = {
	0, 0, -1,
	0, 0,  0,
	0, 1,  0,
	0, 1, -1
};

SegmentMeshMaker::Face SegmentMeshMaker::s_right = {
	1, 0,  0,
	1, 0, -1,
	1, 1, -1,
	1, 1,  0
};

SegmentMeshMaker::Face SegmentMeshMaker::s_top = {
	0, 1,  0,
	1, 1,  0,
	1, 1, -1,
	0, 1, -1
};

SegmentMeshMaker::Face SegmentMeshMaker::s_bottom = {
	0, 0, -1,
	1, 0, -1,
	1, 0,  0,
	0, 0,  0
};

SegmentMeshMaker::Face SegmentMeshMaker::s_crossA = {
	0, 0, -1,
	1, 0,  0,
	1, 1,  0,
	0, 1, -1
};

SegmentMeshMaker::Face SegmentMeshMaker::s_crossB = {
	1, 0, -1,
	0, 0,  0,
	0, 1,  0,
	1, 1, -1
};

const GLfloat SegmentMeshMaker::s_topLight = 1.0f;
const GLfloat SegmentMeshMaker::s_sideLight = 0.6f;
const GLfloat SegmentMeshMaker::s_bottomLight = 0.4f;

void SegmentMeshMaker::makeMesh(MeshTypes& meshes, const Segment& segment) {
	MeshGenerator solidMesh(meshes.solid.mesh);
	MeshGenerator liquidMesh(meshes.liquid.mesh);
	MeshGenerator floraMesh(meshes.flora.mesh);

	auto* top    = segment.getRelativeSegment( 0,  1,  0);
	auto* bottom = segment.getRelativeSegment( 0, -1,  0);
	auto* left   = segment.getRelativeSegment(-1,  0,  0);
	auto* right  = segment.getRelativeSegment( 1,  0,  0);
	auto* front  = segment.getRelativeSegment( 0,  0,  1);
	auto* back   = segment.getRelativeSegment( 0,  0, -1);

	auto& worldPos = segment.getWorldPosition();

	if (segment.isEmpty())
		return;
	if (top && bottom) {
		if (segment.isAllOpaque() && top->isAllOpaque() && bottom->isAllOpaque() &&
			left->isAllOpaque() && right->isAllOpaque() && front->isAllOpaque() &&
			back->isAllOpaque()) {
			return;
		}
	}

	Neighbors vxl;

	auto setNeighbors = [&](std::int16_t x, std::int16_t y, std::int16_t z) {
		vxl[VOXEL]  = segment.getVoxel(x, y, z);

		vxl[TOP]    = SegmentBounds::getInstance().getVoxel(segment, x    , y + 1,  z    );
		vxl[BOTTOM] = SegmentBounds::getInstance().getVoxel(segment, x    , y - 1,  z    );
		vxl[LEFT]   = SegmentBounds::getInstance().getVoxel(segment, x - 1, y    ,  z    );
		vxl[RIGHT]  = SegmentBounds::getInstance().getVoxel(segment, x + 1, y    ,  z    );
		vxl[FRONT]  = SegmentBounds::getInstance().getVoxel(segment, x    , y    ,  z + 1);
		vxl[BACK]   = SegmentBounds::getInstance().getVoxel(segment, x    , y    ,  z - 1);
	};

	auto shouldAddBlob = [&](int voxel) {
		if (vxl[VOXEL].getInfo().shaderType == Voxel::ShaderType::LIQUID) {
			if (voxel == TOP) {
				return vxl[VOXEL] != vxl[voxel].getType(); // for liquids dont cull opaque top sides.
			}
		}
		return !vxl[voxel].getInfo().opaque && vxl[VOXEL] != vxl[voxel].getType();
	};

	for (std::int16_t x = 0; x < Segment::WIDTH; x++)
	for (std::int16_t y = 0; y < Segment::WIDTH; y++)
	for (std::int16_t z = 0; z < Segment::WIDTH; z++) {
		if (segment.getVoxel(x, y, z) == Voxel::Type::VOID)
			continue;
		setNeighbors(x, y, z);

		std::int16_t oX = x + worldPos.x * Segment::WIDTH;
		std::int16_t oY = y + worldPos.y * Segment::WIDTH;
		std::int16_t oZ = z + worldPos.z * Segment::WIDTH;

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
			for (int i = 1; i < 7; i++) {
				if (!vxl[i].getInfo().opaque) {
					addCubeFace(currentMesh, vxl, oX, oY, oZ, i);
				}
			}
			break;
		case Voxel::Shape::BLOB:
			for (int i = 1; i < 7; i++) {
				if (shouldAddBlob(i)) {
					addCubeFace(currentMesh, vxl, oX, oY, oZ, i);
				}
			}
			break;
		case Voxel::Shape::CROSS:
			currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texTop, s_crossA, (float)vxl[RIGHT].getNaturalLight() * s_sideLight);
			currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texTop, s_crossB, (float)vxl[LEFT].getNaturalLight() * s_sideLight);
			break;
		}
	}
}

void SegmentMeshMaker::addCubeFace(MeshGenerator* mesh, const Neighbors& neighbors, int x, int y, int z, int neighbor) {
	auto& voxel = neighbors[VOXEL];
	auto& neighborVoxel = neighbors[neighbor];
	Face* face = nullptr;
	int texture = 0;
	float lightMultiplier = 0.0f;

	switch (neighbor) {
	case TOP:
		face = &s_top;
		texture = voxel.getInfo().texTop;
		lightMultiplier = s_topLight;
		break;
	case BOTTOM:
		face = &s_bottom;
		texture = voxel.getInfo().texBottom;
		lightMultiplier = s_bottomLight;
		break;
	case LEFT:
		face = &s_left;
		texture = voxel.getInfo().texSide;
		lightMultiplier = s_sideLight;
		break;
	case RIGHT:
		face = &s_right;
		texture = voxel.getInfo().texSide;
		lightMultiplier = s_sideLight;
		break;
	case FRONT:
		face = &s_front;
		texture = voxel.getInfo().texSide;
		lightMultiplier = s_sideLight;
		break;
	case BACK:
		face = &s_back;
		texture = voxel.getInfo().texSide;
		lightMultiplier = s_sideLight;
		break;
	}

	mesh->addFace(x, y, z, texture, *face, (float)neighborVoxel.getNaturalLight() * lightMultiplier);
}