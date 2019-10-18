#include "stdafx.h"
#include "vector3.h"

bool operator==(const Vector3& lhs, const Vector3& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool operator!=(const Vector3 & lhs, const Vector3 & rhs) {
	return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z;
}