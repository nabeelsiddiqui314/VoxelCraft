#include "stdafx.h"
#include "SegmentMeshGenerator.h"
#include "Segment.h"
#include "SegmentBounds.h"
#include "CubeFaceMeshes.h"

typedef std::array<Voxel::Element, 7> Neighbors;

enum {
	VOXEL,
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	FRONT,
	BACK
};

void addCubeFace(SegmentMesh* mesh, const Neighbors& neighbors, int x, int y, int z, int neighbor);

void generateMesh(MeshTypes& meshes, const Segment& segment) {
	SegmentMesh solidMesh(meshes.solid.mesh);
	SegmentMesh liquidMesh(meshes.liquid.mesh);
	SegmentMesh floraMesh(meshes.flora.mesh);

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

		SegmentMesh* currentMesh = nullptr;
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
			currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texTop, MeshFace::crossA.mesh, (float)(vxl[RIGHT].getNaturalLight() + 1) * MeshFace::right.light, vxl[RIGHT].getSkyExposure() + 1);
			currentMesh->addFace(oX, oY, oZ, vxl[VOXEL].getInfo().texTop, MeshFace::crossB.mesh, (float)(vxl[RIGHT].getNaturalLight() + 1) * MeshFace::right.light, vxl[RIGHT].getSkyExposure() + 1);
			break;
		}
	}
}

void addCubeFace(SegmentMesh* mesh, const Neighbors& neighbors, int x, int y, int z, int neighbor) {
	auto& voxel = neighbors[VOXEL];
	auto& neighborVoxel = neighbors[neighbor];
	CubeFace* face = nullptr;
	int texture = 0;

	switch (neighbor) {
	case TOP:
		face = &MeshFace::top;
		texture = voxel.getInfo().texTop;
		break;
	case BOTTOM:
		face = &MeshFace::bottom;
		texture = voxel.getInfo().texBottom;
		break;
	case LEFT:
		face = &MeshFace::left;
		texture = voxel.getInfo().texSide;
		break;
	case RIGHT:
		face = &MeshFace::right;
		texture = voxel.getInfo().texSide;
		break;
	case FRONT:
		face = &MeshFace::front;
		texture = voxel.getInfo().texSide;
		break;
	case BACK:
		face = &MeshFace::back;
		texture = voxel.getInfo().texSide;
		break;
	}

	mesh->addFace(x, y, z, texture, face->mesh, (float)(neighborVoxel.getNaturalLight() + 1) * face->light, neighborVoxel.getSkyExposure() + 1);
}