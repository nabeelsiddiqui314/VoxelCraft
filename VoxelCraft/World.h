#pragma once
#include "ChunkManager.h"
#include "FlatGenerator.h"
#include "OverworldGenerator.h"
#include "MasterRenderer.h"
#include <memory>
#include <thread>
#include <mutex>

class World
{
public:
	World();
	~World();
public:
	void update(const Camera& camera);
	void renderChunks(MasterRenderer& renderer);
	void loadChunks();
	void makeMeshes();
private:
	ChunkManager m_chunks;
	VecXZ m_camPosition;
	std::unique_ptr<MapGenerator> m_mapGenerator;
	const int m_renderDistance;
	std::vector<std::thread> m_threads;
	std::mutex m_mutex;
	bool m_running = true;
};