#pragma once
#include <unordered_map>
#include "vecXZ.h"
#include "Chunks.h"
#include <functional>
#include <algorithm>
#include <utility>

class ChunkManager
{
public:
	ChunkManager() = default;
	~ChunkManager();
public:
	void loadChunk(const VecXZ& pos, const Chunks& chunks);
	void unloadChunks(const std::function<bool(const VecXZ& pos)>& cond);

	bool doesChunkExist(const VecXZ& pos) const;

	void setBlock(const VecXZ& pos, std::int16_t x, std::int16_t y, std::int16_t z, BlockType id);
	BlockType getBlock(const VecXZ& pos, std::int16_t x, std::int16_t y, std::int16_t z) const;

	void makeMesh(const VecXZ& pos);
	const Chunks& getChunkAt(const VecXZ& pos) const;
	void regenMesh(const VecXZ& pos, std::int16_t y);

	void render(const VecXZ& pos, MasterRenderer& renderer);
private:
	std::unordered_map<VecXZ, Chunks> m_chunks;
};

