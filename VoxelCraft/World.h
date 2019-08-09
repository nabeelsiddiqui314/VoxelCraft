#pragma once
#include "ChunkManager.h"
#include "FlatGenerator.h"
#include "MeshGenerator.h"
#include <memory>

class World
{
public:
	World();
public:
	Model get();
	void update();
private:
	ChunkManager m_chunks;
	std::unique_ptr<MapGenerator> m_mapGenerator;
	MeshGenerator m_meshGenerator;
};