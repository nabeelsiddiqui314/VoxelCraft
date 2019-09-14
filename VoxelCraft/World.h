#pragma once
#include "ChunkManager.h"
#include "OverworldGenerator.h"
#include "MasterRenderer.h"
#include <memory>

class World
{
public:
	World();
public:
	void update(MasterRenderer& renderer);
private:
	ChunkManager m_chunks;
	std::unique_ptr<OverworldGenerator> m_mapGenerator;
	std::vector<VecXZ> m_chunkBatch;
	std::int16_t m_batchIndex = 0;
	int modelCount = 0;
};