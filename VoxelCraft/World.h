#pragma once
#include "ChunkManager.h"
#include "FlatGenerator.h"
#include "OverworldGenerator.h"
#include "MasterRenderer.h"
#include <memory>
#include <thread>
#include <mutex>
#include <unordered_set>

class World
{
public:
	World();
	~World();
public:
	void update(const Camera& camera);
	void renderChunks(MasterRenderer& renderer, const Frustum& frustum);
private:
	void loadChunks();
	void makeMeshes();
	void makeEditedMeshes();
private:
	ChunkManager m_chunks;
	std::unordered_set<VecXZ> m_regenChunks;
	VecXZ m_camPosition;
	std::unique_ptr<MapGenerator> m_mapGenerator;
	const int m_renderDistance;
	std::vector<std::thread> m_threads;
	std::mutex m_mutex;
	bool m_running = true;
	int m_chunkLoadRadius = 0;
};