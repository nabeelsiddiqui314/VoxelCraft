#include "stdafx.h"
#include "World.h"

World::World() {
	m_mapGenerator = std::make_unique<FlatGenerator>();
	m_chunks.loadChunk({ 0,0 }, m_mapGenerator->generateChunk({0,0}));
}