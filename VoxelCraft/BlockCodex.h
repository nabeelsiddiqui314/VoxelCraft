#pragma once
#include "BlockTypes.h"
#include "BlockData.h"
#include <array>

class BlockCodex
{
	BlockCodex() = delete;
public:
	static void init();
	static const BlockData& getBlockData(BlockType id);
private:
	static std::size_t index(BlockType block);
private:
	static std::array<BlockData, static_cast<std::size_t>(BlockType::COUNT)> s_blocks;
};

