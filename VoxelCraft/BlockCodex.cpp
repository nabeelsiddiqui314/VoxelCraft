#include "stdafx.h"
#include "BlockCodex.h"

std::array<BlockData, static_cast<std::size_t>(BlockType::COUNT)> BlockCodex::s_blocks;

void BlockCodex::init() {
	s_blocks[static_cast<std::size_t>(BlockType::VOID)]  = BlockData();
	s_blocks[static_cast<std::size_t>(BlockType::GRASS)] = BlockData(0, 1, 2, BlockShape::CUBE, ShaderType::SOLID , true);
	s_blocks[static_cast<std::size_t>(BlockType::DIRT)]  = BlockData(2, 2, 2, BlockShape::CUBE, ShaderType::SOLID , true);
	s_blocks[static_cast<std::size_t>(BlockType::STONE)] = BlockData(3, 3, 3, BlockShape::CUBE, ShaderType::SOLID , true);
	s_blocks[static_cast<std::size_t>(BlockType::SAND)]  = BlockData(4, 4, 4, BlockShape::CUBE, ShaderType::SOLID , true);
	s_blocks[static_cast<std::size_t>(BlockType::WATER)] = BlockData(5, 5, 5, BlockShape::PLANE, ShaderType::LIQUID, false);
	s_blocks[static_cast<std::size_t>(BlockType::ROSE)]  = BlockData(6, 6, 6, BlockShape::CROSS, ShaderType::FLORA, false);
	s_blocks[static_cast<std::size_t>(BlockType::SHRUB)] = BlockData(7, 7, 7, BlockShape::CROSS, ShaderType::FLORA, false);
}

const BlockData& BlockCodex::getBlockData(BlockType id) {
	return s_blocks[static_cast<std::size_t>(id)];
}