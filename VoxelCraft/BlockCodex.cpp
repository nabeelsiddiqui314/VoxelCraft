#include "stdafx.h"
#include "BlockCodex.h"

std::array<BlockData, static_cast<std::size_t>(BlockType::COUNT)> BlockCodex::s_blocks;

BlockCodex::BlockCodex() {
	s_blocks[static_cast<std::size_t>(BlockType::VOID)] = BlockData();
	s_blocks[static_cast<std::size_t>(BlockType::GRASS)] = BlockData({ 0,0 }, { 1,0 }, {2,0}, true);
}

const BlockData& BlockCodex::getBlockData(BlockType id) {
	return s_blocks[static_cast<std::size_t>(id)];
}
