#pragma once
#include <glm/glm.hpp>

struct AABB
{
	glm::vec3 position;
	glm::vec3 dimensions;

	glm::vec3 getVN(const glm::vec3& normal)  const
	{
		glm::vec3 res = position;

		if (normal.x < 0) {
			res.x += dimensions.x;
		}

		if (normal.y < 0) {
			res.y += dimensions.y;
		}

		if (normal.z < 0) {
			res.z += dimensions.z;
		}

		return res;
	}

	glm::vec3 getVP(const glm::vec3& normal) const
	{
		glm::vec3 res = position;

		if (normal.x > 0) {
			res.x += dimensions.x;
		}

		if (normal.y > 0) {
			res.y += dimensions.y;
		}

		if (normal.z > 0) {
			res.z += dimensions.z;
		}

		return res;
	}
};

