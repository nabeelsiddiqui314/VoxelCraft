#pragma once
#include "MeshGenerator.h"
#include "BlockCodex.h"
#include "SegmentModel.h"

class Segment;

class SegmentMeshMaker
{
public:
	SegmentMeshMaker(MeshTypes& meshes, std::int16_t originX, std::int16_t originY, std::int16_t originZ,
		const Segment* chunk,
		const Segment* top, const Segment* bottom,
		const Segment* left, const Segment* right,
		const Segment* front, const Segment* back);
private:
	static const std::array<GLfloat, 12> s_front;
	static const std::array<GLfloat, 12> s_back;
	static const std::array<GLfloat, 12> s_right;
	static const std::array<GLfloat, 12> s_left;
	static const std::array<GLfloat, 12> s_top;
	static const std::array<GLfloat, 12> s_bottom;

	static const GLfloat s_topLight;
	static const GLfloat s_sideLight;
	static const GLfloat s_bottomLight;
};

