#pragma once
#include "ChunkManager.h"
#include "FlatGenerator.h"
#include "OverworldGenerator.h"
#include "MasterRenderer.h"
#include <memory>

class World
{
public:
	World();
public:
	void update(const Camera& camera);
	void renderChunks(MasterRenderer& renderer);
private:
	ChunkManager m_chunks;
	VecXZ m_camPosition;
	VecXZ m_lastCamPosition;
	std::unique_ptr<MapGenerator> m_mapGenerator;
	std::vector<VecXZ> m_chunkBatch;
	std::int16_t m_batchIndex = 0;
	sf::Clock m_loadTick;
	const int m_renderDistance;
};