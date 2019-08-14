#pragma once
#include "ChunkManager.h"
#include "FlatGenerator.h"
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
	std::unique_ptr<MapGenerator> m_mapGenerator;
	std::vector<Model> m_chunkModels;
};