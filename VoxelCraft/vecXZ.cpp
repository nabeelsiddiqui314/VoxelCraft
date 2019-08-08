#include "stdafx.h"
#include "vecXZ.h"

bool operator==(const VecXZ& lhs, const VecXZ& rhs) {
 return lhs.x == rhs.x && lhs.z == rhs.z;
}