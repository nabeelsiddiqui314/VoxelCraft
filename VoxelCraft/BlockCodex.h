#pragma once
#include "BlockTypes.h"
#include "BlockData.h"
#include <array>

class BlockCodex
{
private:
	BlockCodex();
public:
	static const BlockData& getBlockData(Block_id id);
private:
	static std::array<BlockData, static_cast<std::size_t>(BlockType::COUNT)> s_blocks;
};

