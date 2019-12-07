#pragma once
#include "MeshGenerator.h"
#include "SegmentModel.h"
#include "VoxelElement.h"

class Segment;

class SegmentMeshMaker
{
private:
	typedef const std::array<GLfloat, 12> Face;
	typedef std::array<Voxel::Element, 7> Neighbors;
private:
	enum {
		VOXEL,
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		FRONT,
		BACK
	};
public:
	SegmentMeshMaker() = delete;
	~SegmentMeshMaker() = default;
public:
	static void makeMesh(MeshTypes& meshes, const Segment& segment);
private:
	static void addCubeFace(MeshGenerator* mesh, const Neighbors& neighbors, int x, int y, int z, int neighbor);
private:
	static const Face s_front;
	static const Face s_back;
	static const Face s_right;
	static const Face s_left;
	static const Face s_top;
	static const Face s_bottom;
	static const Face s_crossA;
	static const Face s_crossB;

	static const GLfloat s_topLight;
	static const GLfloat s_sideLight;
	static const GLfloat s_bottomLight;
};

