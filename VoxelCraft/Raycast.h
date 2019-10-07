#pragma once
#include <glm/glm.hpp>

class RayCast
{
public:
	RayCast(const glm::vec3& origin, const glm::vec3& dir);
	~RayCast() = default;
public:
	const glm::vec3& getDestination() const;

	void traverse();
private:
	glm::vec3 m_origin;
	glm::vec3 m_direction;
	glm::vec3 m_destination;
};