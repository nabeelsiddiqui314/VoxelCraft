#pragma once
#include "ChunkManager.h"
#include "FlatGenerator.h"
#include "OverworldGenerator.h"
#include "MasterRenderer.h"
#include "vector3.h"
#include <memory>
#include <thread>
#include <mutex>
#include <unordered_set>

class World : public NonCopyable
{
public:
	World();
	~World();
public:
	void setBlock(std::int64_t x, std::int64_t y, std::int64_t z, BlockType block);
	BlockType getBlock(std::int64_t x, std::int64_t y, std::int64_t z) const;

	void update(const Camera& camera);
	void renderChunks(MasterRenderer& renderer, const Frustum& frustum);
private:
	void makeChunks();
	void updateBlocks();

	void makeEditedMeshes();
	void updateMeshes(const VecXZ& pos, std::int16_t y);
	void addToUpdates(int x, int y, int z);

	const VecXZ getChunkPos(std::int64_t x, std::int64_t z) const;
	const std::tuple<int, int, int> getBlockPos(std::int64_t x, std::int64_t y, std::int64_t z) const;
private:
	ChunkManager m_chunks;
	std::unordered_set<VecXZ> m_regenChunks;
	std::unordered_set<Vector3> m_updateList;
	VecXZ m_camPosition;
	std::unique_ptr<MapGenerator> m_mapGenerator;
	const int m_renderDistance;
	std::vector<std::thread> m_threads;
	mutable std::recursive_mutex m_mutex;
	bool m_running = true;
	int m_currentRadius = 0;
};