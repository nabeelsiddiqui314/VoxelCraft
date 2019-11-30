#pragma once
#include "MeshGenerator.h"
#include "SegmentModel.h"

class Segment;

class SegmentMeshMaker
{
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
	SegmentMeshMaker(MeshTypes& meshes, const Segment& segment);
private:
	static const std::array<GLfloat, 12> s_front;
	static const std::array<GLfloat, 12> s_back;
	static const std::array<GLfloat, 12> s_right;
	static const std::array<GLfloat, 12> s_left;
	static const std::array<GLfloat, 12> s_top;
	static const std::array<GLfloat, 12> s_bottom;
	static const std::array<GLfloat, 12> s_crossA;
	static const std::array<GLfloat, 12> s_crossB;

	static const GLfloat s_topLight;
	static const GLfloat s_sideLight;
	static const GLfloat s_bottomLight;
};

