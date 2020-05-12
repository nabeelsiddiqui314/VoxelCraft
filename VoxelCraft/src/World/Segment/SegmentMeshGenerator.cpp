#include "SegmentMeshGenerator.h"
#include "Segment.h"
#include "CubeFaceMeshes.h"
#include "SegmentMesh.h"
#include "SegmentModel.h"

enum {
	VOXEL,
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	FRONT,
	BACK
};

void SegmentMeshGenerator::generateMesh(MeshTypes& meshes, const Vector3& worldPos, const Segment& segment) {
	if (segment.getNeighbor(Segment::NeighborPosition::LEFT) &&
		segment.getNeighbor(Segment::NeighborPosition::RIGHT) &&
		segment.getNeighbor(Segment::NeighborPosition::FRONT) &&
		segment.getNeighbor(Segment::NeighborPosition::BACK)) {

		SegmentMesh solidMesh(meshes.solid.mesh);
		SegmentMesh liquidMesh(meshes.liquid.mesh);
		SegmentMesh floraMesh(meshes.flora.mesh);

		auto top = segment.getNeighbor(Segment::NeighborPosition::TOP);
		auto bottom = segment.getNeighbor(Segment::NeighborPosition::BOTTTOM);
		auto left = segment.getNeighbor(Segment::NeighborPosition::LEFT);
		auto right = segment.getNeighbor(Segment::NeighborPosition::RIGHT);
		auto front = segment.getNeighbor(Segment::NeighborPosition::FRONT);
		auto back = segment.getNeighbor(Segment::NeighborPosition::BACK);

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
			vxl[VOXEL] = segment.getVoxel(x, y, z);

			vxl[TOP] = segment.getVoxelFromNeighborhood(x, y + 1, z);
			vxl[BOTTOM] = segment.getVoxelFromNeighborhood(x, y - 1, z);
			vxl[LEFT] = segment.getVoxelFromNeighborhood(x - 1, y, z);
			vxl[RIGHT] = segment.getVoxelFromNeighborhood(x + 1, y, z);
			vxl[FRONT] = segment.getVoxelFromNeighborhood(x, y, z + 1);
			vxl[BACK] = segment.getVoxelFromNeighborhood(x, y, z - 1);
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
}

void SegmentMeshGenerator::addCubeFace(SegmentMesh* mesh, const Neighbors& neighbors, int x, int y, int z, int neighbor) {
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