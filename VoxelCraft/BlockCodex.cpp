#include "stdafx.h"
#include "BlockCodex.h"

std::array<BlockData, static_cast<std::size_t>(BlockType::COUNT)> BlockCodex::s_blocks;

void BlockCodex::init() {
	s_blocks[index(BlockType::VOID)]  = BlockData();
	s_blocks[index(BlockType::GRASS)] = BlockData(std::make_unique<BlockUpdateHandler>(), 0, 1, 2, BlockShape::CUBE, ShaderType::SOLID , true);
	s_blocks[index(BlockType::DIRT)]  = BlockData(std::make_unique<BlockUpdateHandler>(), 2, 2, 2, BlockShape::CUBE, ShaderType::SOLID , true);
	s_blocks[index(BlockType::STONE)] = BlockData(std::make_unique<BlockUpdateHandler>(), 3, 3, 3, BlockShape::CUBE, ShaderType::SOLID , true);
	s_blocks[index(BlockType::SAND)]  = BlockData(std::make_unique<BlockUpdateHandler>(), 4, 4, 4, BlockShape::CUBE, ShaderType::SOLID , true);
	s_blocks[index(BlockType::WATER)] = BlockData(std::make_unique<LiquidHandler>(),      5, 5, 5, BlockShape::BLOB, ShaderType::LIQUID, false);
	s_blocks[index(BlockType::ROSE)]  = BlockData(std::make_unique<GroundFloraHandler>(), 6, 6, 6, BlockShape::CROSS, ShaderType::FLORA, false);
	s_blocks[index(BlockType::SHRUB)] = BlockData(std::make_unique<GroundFloraHandler>(), 7, 7, 7, BlockShape::CROSS, ShaderType::FLORA, false);
}

const BlockData& BlockCodex::getBlockData(BlockType id) {
	return s_blocks[static_cast<std::size_t>(id)];
}

std::size_t BlockCodex::index(BlockType block) {
	return static_cast<std::size_t>(block);
}