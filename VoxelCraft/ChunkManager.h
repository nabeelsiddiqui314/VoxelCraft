#pragma once
#include <unordered_map>
#include "vecXZ.h"
#include "Chunk.h"

class ChunkManager
{
public:
	ChunkManager() = default;
	~ChunkManager();
public:
	void loadChunk(const VecXZ& pos, const ChunkBlocks& chunkblocks);
	void unloadChunk(const VecXZ& pos);
	bool doesChunkExist(const VecXZ& pos) const;
	void setBlock(const VecXZ& pos, std::int16_t x, std::int16_t y, std::int16_t z, BlockType id);
	BlockType getBlock(const VecXZ& pos, std::int16_t x, std::int16_t y, std::int16_t z) const;
	void createMesh(const VecXZ& pos);
	const ChunkModels& getChunkModels(const VecXZ& pos) const;
	bool hasMesh(const VecXZ& pos) const;
	void updateMeshStatus(const VecXZ& pos);
private:
	std::unordered_map<VecXZ, Chunk> m_chunks;
};

