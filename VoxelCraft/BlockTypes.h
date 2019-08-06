#pragma once
#include <cstdint>

typedef std::uint8_t Block_id;

enum class BlockType : Block_id {
	VOID = 0,
	GRASS = 1,
	COUNT
};