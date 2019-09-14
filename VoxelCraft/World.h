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
	void update(const Camera& camera, MasterRenderer& renderer);
private:
	void readyChunk(std::int16_t x, std::int16_t z);
private:
	ChunkManager m_chunks;
	glm::vec2 m_camPosition;
	glm::vec2 m_lastCamPosition;
	std::unique_ptr<OverworldGenerator> m_mapGenerator;
	std::vector<VecXZ> m_chunkBatch;
	std::int16_t m_batchIndex = 0;
};