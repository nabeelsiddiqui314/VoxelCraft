#pragma once
#include <cstdint>
#include <functional>

struct Vector3
{
	int x, y, z;
};

bool operator==(const Vector3& lhs, const Vector3& rhs);
bool operator!=(const Vector3& lhs, const Vector3& rhs);

namespace std {
	template<>
	struct hash<Vector3> {
		size_t operator()(const Vector3& vec) const {
			std::hash<int> hasher;
			auto hashx = hasher(vec.x);
			auto hashy = hasher(vec.y);
			auto hashz = hasher(vec.z);

			return std::hash<int>{}((hashx ^ (hashy << hashz) ^ hashz));
		}
	};
}