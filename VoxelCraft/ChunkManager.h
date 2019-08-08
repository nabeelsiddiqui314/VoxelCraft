#pragma once
#include "Chunk.h"
#include <unordered_map>
#include "vecXZ.h"

class VecXZ;

class ChunkManager
{
public:
	ChunkManager() = default;
	~ChunkManager();
public:
	void loadChunk(const VecXZ& pos, const Chunk& chunk);
	void unloadChunk(const VecXZ& pos);
	void setBlock(std::int16_t x, std::int16_t y, std::int16_t z, BlockType id);
	BlockType getBlock(std::int16_t x, std::int16_t y, std::int16_t z) const;
private:
	std::unordered_map<VecXZ, Chunk> m_chunks;
};

