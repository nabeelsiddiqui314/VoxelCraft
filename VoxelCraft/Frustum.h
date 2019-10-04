#pragma once
#include <array>
#include "Plane.h"
#include "AABB.h"

class Frustum
{
private:
	enum {
		NEARP = 0,
		FARP,
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};
public:
	Frustum() = default;
	~Frustum() = default;
public:
	void updateFrustum(const glm::mat4& mat);
	bool isBoxInFrustum(const AABB& box) const;
private:
	std::array<Plane, 6> m_planes;
};

