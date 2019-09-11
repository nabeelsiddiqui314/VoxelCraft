#include "stdafx.h"
#include "BlockCodex.h"

std::array<BlockData, static_cast<std::size_t>(BlockType::COUNT)> BlockCodex::s_blocks;

void BlockCodex::init() {
	s_blocks[static_cast<std::size_t>(BlockType::VOID)] = BlockData();
	s_blocks[static_cast<std::size_t>(BlockType::GRASS)] = BlockData(0, 1, 2, BlockCategory::SOLID, true);
	s_blocks[static_cast<std::size_t>(BlockType::DIRT)] = BlockData(2, 2, 2, BlockCategory::SOLID, true);
	s_blocks[static_cast<std::size_t>(BlockType::STONE)] = BlockData(3, 3, 3, BlockCategory::SOLID, true);
	s_blocks[static_cast<std::size_t>(BlockType::SAND)] = BlockData(4, 4, 4, BlockCategory::SOLID, true);
}

const BlockData& BlockCodex::getBlockData(BlockType id) {
	return s_blocks[static_cast<std::size_t>(id)];
}