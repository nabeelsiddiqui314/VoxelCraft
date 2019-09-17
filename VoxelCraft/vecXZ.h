#pragma once
#include <cstdint>
#include <functional>

struct VecXZ {
	std::int16_t x, z;
};

bool operator==(const VecXZ& lhs, const VecXZ& rhs);
bool operator!=(const VecXZ& lhs, const VecXZ& rhs);

namespace std {
	template<>
	struct hash<VecXZ> {
		size_t operator()(const VecXZ& vec) const {
			std::hash<std::int16_t> hasher;
			auto hashx = hasher(vec.x);
			auto hashz = hasher(vec.z);

			return std::hash<std::size_t>{}((hashx ^ hashz) >> 2);
		}
	};
}