#pragma once
#include <cstdint>

namespace Voxel {
	enum class Type : std::uint8_t {
		VOID = 0,
		GRASS,
		DIRT,
		STONE,
		SAND,
		WATER,
		ROSE,
		SHRUB,

		COUNT
	};

	enum class Shape : std::uint8_t {
		CUBE,
		BLOB,
		CROSS
	};

	enum class ShaderType : std::uint8_t {
		SOLID,
		LIQUID,
		FLORA
	};
}