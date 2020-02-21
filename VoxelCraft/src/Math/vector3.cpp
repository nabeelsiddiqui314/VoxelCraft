#include "vector3.h"

bool operator==(const Vector3& lhs, const Vector3& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool operator!=(const Vector3 & lhs, const Vector3 & rhs) {
	return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z;
}

Vector3::Vector3(int _x, int _y, int _z) 
: x(_x), y(_y), z(_z){}