#pragma once
#include <glm/glm.hpp>

struct Plane
{
	glm::vec3 normal;
	float d;

	Plane() = default;
	~Plane() = default;

	float distance(const glm::vec3& p) const;
};

