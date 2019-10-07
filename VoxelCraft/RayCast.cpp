#include "stdafx.h"
#include "RayCast.h"



RayCast::RayCast(const glm::vec3 & origin, const glm::vec3& dir) 
: m_origin(origin),
  m_direction(dir),
  m_destination(origin) {}

const glm::vec3& RayCast::getDestination() const {
	return m_destination;
}

void RayCast::traverse() {
	m_destination += m_direction;
}
