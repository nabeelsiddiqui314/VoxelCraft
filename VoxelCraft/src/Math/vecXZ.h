#pragma once
#include <cstdint>
#include <functional>

struct VecXZ {
	int x, z;
};

bool operator==(const VecXZ& lhs, const VecXZ& rhs);
bool operator!=(const VecXZ& lhs, const VecXZ& rhs);

namespace std {
	template<>
	struct hash<VecXZ> {
		size_t operator()(const VecXZ& vec) const {
			std::hash<decltype(vec.x)> hasher;
			auto hashx = hasher(vec.x);
			auto hashz = hasher(vec.z);

			return std::hash<std::size_t>{}((hashx ^ hashz) >> 2);
		}
	};
}