#pragma once
#include "ChunkManager.h"
#include "FlatGenerator.h"
#include <memory>

class World
{
public:
	World();
public:

private:
	ChunkManager m_chunks;
	std::unique_ptr<MapGenerator> m_mapGenerator;
};